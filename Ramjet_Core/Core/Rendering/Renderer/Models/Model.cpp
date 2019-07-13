#include <CoreBasicInclude.h>
#include "Model.h"

#include <Utils/String.h>
#include <Utils/StringUtils.h>
#include <Utils/Fileutils.h>

#include <GLEW/glew.h>

namespace Core 
{
	namespace Rendering 
	{

		Model::Model(const String& path, MaterialInstance* materialInstance)
		{
			load(path);
			for (Mesh* mesh : m_Meshs)
				mesh->setMaterial(materialInstance);
		}

		Model::~Model()
		{
			for (Mesh* mesh : m_Meshs)
				delete mesh;
			m_Meshs.clear();
		}

		void Model::render(Renderer3D& renderer)
		{
			for (Mesh* mesh : m_Meshs)
				mesh->render(renderer);
		}

		void Model::load(const String& path)
		{
			Assimp::Importer import;
			const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
			{
				CORE_ERROR("Assimp error, could not load file ", path.c_str(), import.GetErrorString());
				return;
			}
			
			processNode(scene->mRootNode, scene);
		}

		void Model::processNode(aiNode* node, const aiScene* scene)
		{
			for(uint i = 0; i < node->mNumMeshes; i++) 
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				processMesh(mesh, scene);
				// TODO TEXTURE !!
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				processNode(node->mChildren[i], scene);
			}
		}

		void Model::processMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<uint> indices;

			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				Vertex vertex;
				Maths::vec3 vector;

				// position
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.position = vector;
				// normals
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.normal = vector;

				if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
				{
					Maths::vec2 vec;
					// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
					// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
					vec.x = mesh->mTextureCoords[0][i].x;
					vec.y = mesh->mTextureCoords[0][i].y;
					vertex.uv = vec;
				}
				else
					vertex.uv = Maths::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				// retrieve all indices of the face and store them in the indices vector
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}
			
			API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
			buffer->bind();
			buffer->setData(vertices.size() * sizeof(Vertex), &vertices[0]);

			buffer->layout.push<Maths::vec3>("position");
			buffer->layout.push<Maths::vec3>("normal");
			buffer->layout.push<Maths::vec2>("uv");

			VertexArray* va = new VertexArray();
			va->bind();
			va->addBuffer(buffer);

			IndexBuffer* ib = new IndexBuffer(&indices[0], indices.size());
			m_Meshs.push_back(new Mesh(va, ib, nullptr));
		}

	}
}
