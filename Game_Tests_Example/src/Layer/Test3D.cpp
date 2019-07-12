#include "Test3D.h"

using namespace Core;
using namespace Rendering;
using namespace Maths;
using namespace Manager;

Test3D::Test3D()
	: Layer3D(new Scene())
{
	m_Rotation = 0.0f;
	m_SetUniforms[0] = true;
	m_SetUniforms[1] = true;
}

Test3D::~Test3D()
{
}

void Test3D::onInit(Core::Rendering::Renderer3D& renderer, Core::Rendering::Scene& scene)
{
	VertexArray* va = Mesh_Manager::CreateQuad(0, 0, 5, 5);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0, 1, 2, 2, 3, 0 }, 6);

	Shader_Manager::FromFile("SceneShader", "Assets/Shaders/SceneVert.glsl", "Assets/Shaders/SceneFrag.glsl");
	Material* material = new Material(Shader_Manager::get("SceneShader"));
	//m_Cube = Mesh_Manager::CreateCube(5.0f, new MaterialInstance(m_Material));
	material->setUniform("pr_matrix", mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	material->setUniform("vw_matrix", mat4::Translate(vec3(0, 0.0f, -10.0f)));
	material->setUniform("ml_matrix", mat4::Rotate(45.0f, vec3(0, 1, 0)));

	m_CubeMat = new MaterialInstance(material);
	m_SphereMat = new MaterialInstance(material);

	Model* cube = new Model("Assets/Objects/Models/Cube.obj", m_CubeMat);
	Model* sphere = new Model("Assets/Objects/Models/Sphere.obj", m_SphereMat);

	scene.add(sphere);
	scene.add(cube);

}

void Test3D::onTick()
{
	App::Application& app = App::Application::getApplication();
	CORE_INFO(app.getUPS(), " ups, ", app.getFPS(), " fps");
}

float g_Rotation = 0.0f;

void Test3D::onUpdate()
{
	mat4 transform = mat4::Rotate(m_Rotation, vec3(1, 0, 0)) * mat4::Rotate(m_Rotation, vec3(0, 1, 0)) * mat4::Rotate(m_Rotation, vec3(0, 0, 1));
	m_Rotation += 0.5f;

	if (m_SetUniforms[0])
		m_CubeMat->setUniform("ml_matrix", mat4::Translate(vec3(-4, 0, 0)) * transform * mat4::Scale(vec3(1.4f, 1.4f, 1.4f)));
	if (m_SetUniforms[1])
		m_SphereMat->setUniform("ml_matrix", mat4::Translate(vec3(4, 0, 0)) * transform);

	if (C_Manager->isKeyTyped(GLFW_KEY_1))
	{
		m_CubeMat->unsetUniform("ml_matrix");
		m_SetUniforms[0] = !m_SetUniforms[0];
	}
	if (C_Manager->isKeyTyped(GLFW_KEY_2))
	{
		m_SphereMat->unsetUniform("ml_matrix");
		m_SetUniforms[1] = !m_SetUniforms[1];
	}
}

bool Test3D::onEvent()
{
	return false;
}
