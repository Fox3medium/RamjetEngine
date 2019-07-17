#include <Core/CoreBasicInclude.h>
#include "Application.h"
#include <Debug/DebugLayer.h>

namespace App 
{
	using namespace Core::Rendering;

	Application* Application::s_Instance = nullptr;

	void Application::init()
	{
		platformInit();

		m_DebugLayer = new Core::Debug::DebugLayer();
		m_DebugLayer->init();
	}

	void Application::pushLayer(Layer* layer)
	{		
		m_Layers.push_back(layer);
		layer->init();
	}

	Layer* Application::popLayer()
	{
		Layer* layer = m_Layers.back();
		m_Layers.pop_back();
		return layer;
	}

	void Application::pushOverlay(Layer* layer)
	{
		m_OverlayStack.push_back(layer);
		layer->init();
	}

	Layer* Application::popOverlay()
	{
		Layer* layer = m_OverlayStack.back();
		m_OverlayStack.pop_back();
		return layer;
	}

	void Application::tick()
	{
		m_DebugLayer->onTick();
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onTick();

		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onTick();
	}

	void Application::onEvent()
	{
		for (int i = m_OverlayStack.size() - 1; i >= 0; i--)
		{
			m_OverlayStack[i]->onEvent();
		}

		for (int i = m_Layers.size() - 1; i >= 0; i--)
		{
			m_Layers[i]->onEvent();
		}
		m_DebugLayer->onEvent();
	}

	void Application::update()
	{
		m_DebugLayer->onUpdate();

		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onUpdate();

		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onUpdate();
	}

	void Application::render()
	{
		if (Core::Manager::Control_Manager::isKeyEvent())
			onEvent();
		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onRender();
		
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onRender();

		Layer2D* debugLayer = (Layer2D*)m_DebugLayer;
		if (debugLayer->isVisible())
			debugLayer->onRender();
	}

}