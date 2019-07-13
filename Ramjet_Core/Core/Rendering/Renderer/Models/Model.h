#pragma once

#include <Core/Common.h>
#include <CoreBasicInclude.h>

#include <Utils/types.h>
#include <Utils/Maths/maths.h>
#include <Rendering/Renderer/Renderer3D.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

namespace Core 
{
	namespace Rendering 
	{
		class CORE_API Model : public IRenderable
		{
		private:
			std::vector<Mesh*> m_Meshs;

		public:
			Model(const String& path, MaterialInstance* materialInstance);
			Model(Mesh* mesh, MaterialInstance* materialInstance);
			~Model();

			void render(Renderer3D& renderer) override;

			inline std::vector<Mesh*> getMesh() const { return m_Meshs; }

		private:
			struct VertexSet
			{
				std::vector<Maths::vec3> positions;
				std::vector<Maths::vec3> normals;
				std::vector<Maths::vec2> uvs;
			};

			struct IndexSet 
			{
				uint position;
				uint uv;
				uint normal;

				bool operator ==(const IndexSet& other) const 
				{
					return position == other.position && uv == other.uv && normal == other.normal;
				}
			};

			friend struct std::hash<IndexSet>;

			void load(const String& path);
			void processNode(aiNode* node, const aiScene* scene);
			void processMesh(aiMesh* mesh, const aiScene* scene);

		};
	}
}
