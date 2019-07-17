#include "Panel.h"
#include <CoreBasicInclude.h>
#include "Widget.h"
#include <App/Application.h>
#include <Utils/Maths/maths.h>
#include <Managers/Shader_Manager.h>

namespace Core
{
	namespace UI
	{
		using namespace Maths;

		Panel::Panel()
			: Layer2D(Shader_Manager::DefaultShader(), Maths::mat4::Orthographic(0.0f, 32.0f, 0.0f, 18.0f, -1.0f, 1.0f))
		{
			App::Application::getApplication().pushOverlay(this);
		}

		Panel::~Panel()
		{
			for (uint i = 0; i < m_Widgets.size(); i++)
				delete m_Widgets[i];

			App::Application::getApplication().popOverlay(this);
		}

		Widget* Panel::add(Widget* widget)
		{
			m_Widgets.push_back(widget);
			return widget;
		}

		void Panel::remove(Widget* widget)
		{
			int index = 0;
			for (uint i = 0; i < m_Widgets.size(); i++)
			{
				if (m_Widgets[i] == widget)
				{
					m_Widgets.erase(m_Widgets.begin() + i);
					delete m_Widgets[i];
					break;
				}
			}
		}

		void Panel::clear()
		{
			for (uint i = 0; i < m_Widgets.size(); i++)
				delete m_Widgets[i];

			m_Widgets.clear();
		}

		void Panel::onEvent()
		{
			
		}

		bool Panel::onMousePressedEvent()
		{
			vec2 mouse = Init::Window::getWindowClass()->getMousePos();
			for (uint i = 0; i < m_Widgets.size(); i++)
			{
				Widget* widget = m_Widgets[i];
				if (widget->getBounds().Contains(mouse))
				{
					if (widget->onMousePressed())
						return true;
				}
			}
			return false;
		}

		bool Panel::onMouseReleasedEvent()
		{
			vec2 mouse = Init::Window::getWindowClass()->getMousePos();
			for (uint i = 0; i < m_Widgets.size(); i++)
			{
				Widget* widget = m_Widgets[i];
				if (widget->getBounds().Contains(mouse))
				{
					if (widget->onMouseReleased())
						return true;
				}
			}
			return false;
		}

		bool Panel::onMouseMovedEvent()
		{
			for (uint i = 0; i < m_Widgets.size(); i++)
			{
				Widget* widget = m_Widgets[i];
				if (widget->onMouseMoved())
					return true;
			}
			return false;
		}

		void Panel::onUpdate()
		{
			for (Widget* widget : m_Widgets)
			{
				if (widget->isActive())
					widget->onUpdate();
			}
		}

		void Panel::onRender(Renderer2D& renderer)
		{
			for (Widget* widget : m_Widgets)
			{
				if (widget->isActive())
					widget->onRender(renderer);
			}

		}
	}
}