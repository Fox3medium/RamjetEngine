#include "TestLayer.h"

#include <App/Application.h>
#include <Rendering/Renderer/Batch2DRenderer.h>
#include <Rendering/Renderer/Shader/Shader.h>
#include <Rendering/Renderer/Models/Sprite.h>
#include <Managers/Managers.h>

using namespace Core;
using namespace Rendering;
using namespace Manager;
using namespace Maths;

TestLayer::TestLayer()
	: Layer2D(Shader_Manager::DefaultShader(), mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
}

TestLayer::~TestLayer()
{
}

void TestLayer::onInit(Core::Rendering::Renderer2D& renderer, Core::Rendering::Shader& shader)
{
	// WAIT FOR THE WINDOW TO BE INITIALIZED !!
	
	Font_Manager::get()->setScale(m_Window->getWidth() / 32.0f, m_Window->getHeight() / 18.0f);
	renderer.setRenderTarget(RenderTarget::BUFFER);
	renderer.addPostFXPass(	new PostFXPass(Shader_Manager::FromFile("PostFX", "Assets/Shaders/postFXVert.glsl", "Assets/Shaders/postFXFrag.glsl")));
	renderer.setPostFX(false);

	Texture::setFilter(TextureFilter::NEAREST);
	add(new Sprite(0.0f, 0.0f, 8, 8, new Texture("Tex", "Assets/Test/747.png")));
	add(new Sprite(-8.0f, -8.0f, 6, 6, 0xffff00ff));

	m_FPS = new Label("", -15.5f, 7.8f, DEBUG_COLOR_WHITE);
	add(m_FPS);

	m_DebugInfo = new Label * [10];
	m_DebugInfo[0] = new Label("", -15.5f, 6.8f, DEBUG_COLOR_WHITE);
	m_DebugInfo[1] = new Label("", -15.5f, 5.8f, DEBUG_COLOR_WHITE);
	add(m_DebugInfo[0]);
	add(m_DebugInfo[1]);

	Texture::setWrap(TextureWrap::CLAMP_TO_BORDER);
	Mask* mask = new Mask(new Texture("Mask", "Assets/Test/mask.tif"));
	mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));

	Sound_Manager::add(new Sound("test", "Assets/Test/untitled.wav"));
}

void TestLayer::onTick()
{
	App::Application& app = App::Application::getApplication();
	m_FPS->m_Text = std::to_string(app.getFPS()) + " fps";
	CORE_INFO(app.getUPS(), " ups, ", app.getFPS(), " fps");
}

void TestLayer::onEvent()
{
	
}

void TestLayer::onUpdate()
{
}

void TestLayer::onRender(Core::Rendering::Renderer2D& renderer)
{
	if (C_Manager->isKeyTyped(GLFW_KEY_1))
		renderer.setRenderTarget(renderer.getRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
	if (C_Manager->isKeyTyped(GLFW_KEY_2))
		renderer.setPostFX(!renderer.getPostFX());

	m_DebugInfo[0]->m_Text = String("Target: ") + (renderer.getRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
	m_DebugInfo[1]->m_Text = String("PostFX: ") + (renderer.getPostFX() ? "On" : "Off");
}
