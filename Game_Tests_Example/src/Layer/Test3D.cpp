#include "Test3D.h"

using namespace Core;
using namespace Rendering;
using namespace Maths;
using namespace Manager;

Test3D::Test3D()
	: Layer3D(new Scene())
{
	m_Rotation = 0.0f;
}

Test3D::~Test3D()
{
}

void Test3D::onInit(Core::Rendering::Renderer3D& renderer, Core::Rendering::Scene& scene)
{
	VertexArray* va = Mesh_Manager::CreateQuad(0, 0, 5, 5);
	IndexBuffer* ib = new IndexBuffer(new uint[6]{ 0, 1, 2, 2, 3, 0 }, 6);

	Shader_Manager::FromFile("PostFX", "Assets/Shaders/SceneVert.glsl", "Assets/Shaders/SceneFrag.glsl");
	m_Material = new Material(Shader_Manager::get("PostFX"));
	m_Cube = Mesh_Manager::CreateCube(5.0f, new MaterialInstance(m_Material));
	scene.add(m_Cube);

	m_Material->setUniform("pr_matrix", mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
	m_Material->setUniform("vw_matrix", mat4::Translate(vec3(0, 0, -10.0f)));
	m_Material->setUniform("ml_matrix", mat4::Rotate(45.0f, vec3(0, 1, 0)));
}

void Test3D::onTick()
{
	App::Application& app = App::Application::getApplication();
	CORE_INFO(app.getUPS(), " ups, ", app.getFPS(), " fps");
}

float g_Rotation = 0.0f;

void Test3D::onUpdate()
{
	mat4 transform = mat4::Rotate(g_Rotation, vec3(1, 0, 0)) * mat4::Rotate(g_Rotation, vec3(0, 1, 0)) * mat4::Rotate(g_Rotation, vec3(0, 0, 1));
	m_Material->setUniform("ml_matrix", transform);
	g_Rotation += 0.5f;
}

bool Test3D::onEvent()
{
	return false;
}
