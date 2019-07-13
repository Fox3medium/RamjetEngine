#include <Core/CoreBasicInclude.h>
#include "Application.h"

namespace App 
{
	using namespace Core::Rendering;

	Application* Application::s_Instance = nullptr;

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
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onTick();

		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onTick();
	}

	void Application::update()
	{
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onUpdate();

		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onUpdate();
	}

	void Application::render()
	{
		for (uint i = 0; i < m_Layers.size(); i++)
			m_Layers[i]->onRender();
		
		for (uint i = 0; i < m_OverlayStack.size(); i++)
			m_OverlayStack[i]->onRender();
	}

}