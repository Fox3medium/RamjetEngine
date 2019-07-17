#include "DebugLayer.h"

#include <Utils/Maths/maths.h>
#include <Managers/Shader_Manager.h>
#include <Managers/Control_Manager.h>
#include <Rendering/Renderer/Models/Label.h>
#include <Rendering/Renderer/Models/Sprite.h>
#include <CoreBasicInclude.h>
#include <Managers/embed/Embedded.h>
#include <App/Application.h>

namespace Core
{
	namespace Debug
	{
		using namespace Maths;		
		using namespace Manager;

		DebugLayer::DebugLayer()
			: Layer2D(Shader_Manager::DefaultShader(), mat4::Orthographic(0.0f, 32.0f, 0.0f, 18.0f, -1.0f, 1.0f)), 
			m_Application(App::Application::getApplication())
		{
			m_FPSAverage = 0;
			m_UpdateNumber = 0;
		}

		DebugLayer::~DebugLayer()
		{
		}

		void DebugLayer::onInit(Rendering::Renderer2D& renderer, Rendering::Shader& shader)
		{
			DebugMenu::init();
			renderer.setRenderTarget(RenderTarget::SCREEN);
			m_FPSLabel = new Rendering::Label("", 14.0f, 8.5f, Font_Manager::get(), DEBUG_COLOR_WHITE);
			add(m_FPSLabel);

			DebugMenu::add("Example");
			DebugMenu::add("Example");
			
		}

		void DebugLayer::onTick()
		{			
			m_FPSLabel->m_Text = std::to_string(m_Application.getFPS());
		}

		void DebugLayer::onUpdate()
		{
		}

		void DebugLayer::onEvent()
		{
			if (Control_Manager::isKeyPressed(GLFW_KEY_LEFT_CONTROL) 
				&& Control_Manager::isKeyTyped(GLFW_KEY_TAB))
			{
				CORE_INFO("KEY CTRL TAB PRESSED!");
				/*DebugMenu::setVisible(!DebugMenu::isVisible());*/
			}
		}

		bool DebugLayer::onMouseMovedEvent()
		{
			return false;
		}

		bool DebugLayer::onKeyPressedEvent()
		{
			return false;
		}

		void DebugLayer::onRender(Rendering::Renderer2D& renderer)
		{
			/*if (DebugMenu::isVisible())
				DebugMenu::onRender(renderer);*/
		}

	}
}