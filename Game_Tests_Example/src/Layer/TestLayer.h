#pragma once


#include <Rendering/Renderer/Layers/Layer2D.h>
#include <Rendering/Renderer/Models/Label.h>
#include <Rendering/Renderer/Renderer2D.h>
#include <Utils/Log.h>

class TestLayer : public Core::Rendering::Layer2D 
{
private:
	Core::Rendering::Label* m_FPS;
	Core::Rendering::Label** m_DebugInfo;

	Core::Manager::Control_Manager* C_Manager;

public:
	TestLayer();
	~TestLayer();

	void onInit(Core::Rendering::Renderer2D& renderer, Core::Rendering::Shader& shader) override;

	void onTick() override;
	void onEvent() override;
	void onUpdate() override;
	void onRender(Core::Rendering::Renderer2D& renderer) override;
};