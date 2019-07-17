#include "Test3D.h"
#include <Rendering/Renderer/Models/Model.h>

using namespace Core;
using namespace Rendering;
using namespace Maths;
using namespace Manager;
using namespace Entities;
using namespace Components;

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

	m_Cube = new Entity();
	Model* cube = new Model("Assets/Objects/Models/nanosuit.obj", new MaterialInstance(material));
	m_Cube->addModel(cube);
	m_Cube->addComponent(new TransformComponent(mat4::Identity()));

	m_Sphere = new Entity();
	Model* sphere = new Model("Assets/Objects/Models/Sphere.obj", new MaterialInstance(material));
	m_Sphere->addModel(sphere);
	m_Sphere->addComponent(new TransformComponent(mat4::Identity()));

	m_Plane = new Entity();
	Mesh* pl = Mesh_Manager::CreatePlan(32, 32, vec3(0, 1, 0), new MaterialInstance(material));
	Model* plane = new Model(pl, new MaterialInstance(material));
	m_Plane->addModel(plane);
	m_Plane->addComponent(new TransformComponent(mat4::Identity()));

	scene.add(m_Sphere);
	scene.add(m_Cube);
	scene.add(m_Plane);

}

void Test3D::onTick()
{

}

float g_Rotation = 0.0f;

void Test3D::onUpdate()
{
	TransformComponent* cubeTransform = m_Cube->getComponent<TransformComponent>();
	TransformComponent* sphereTransform = m_Sphere->getComponent<TransformComponent>();

	mat4 transform = mat4::Rotate(m_Rotation, vec3(1, 0, 0)) * mat4::Rotate(m_Rotation, vec3(0, 1, 0)) * mat4::Rotate(m_Rotation, vec3(0, 0, 1));
	mat4 c_transform = mat4::Rotate(m_Rotation, vec3(0, 1, 0));
	cubeTransform->transform = mat4::Translate(vec3(-4, 0, 0)) * c_transform * mat4::Scale(vec3(1.4f, 1.4f, 1.4f));
	sphereTransform->transform = mat4::Translate(vec3(4, 2, 0)) * transform;
	m_Rotation++;
}

void Test3D::onEvent()
{
	
}
