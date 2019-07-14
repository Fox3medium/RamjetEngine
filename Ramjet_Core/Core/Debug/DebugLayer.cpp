#include "DebugLayer.h"

#include <Utils/Maths/maths.h>
#include <Managers/Shader_Manager.h>
#include <Managers/Control_Manager.h>
#include <Rendering/Renderer/Models/Label.h>
#include <Rendering/Renderer/Models/Sprite.h>
#include <CoreBasicInclude.h>

namespace Core
{
	namespace Debug
	{
		using namespace Maths;		
		using namespace Manager;

		DebugLayer::DebugLayer()
			: Layer2D(Shader_Manager::DefaultShader(), mat4::Orthographic(0.0f, 32.0f, 0.0f, 18.0f, -1.0f, 1.0f))
		{
		}
		DebugLayer::~DebugLayer()
		{
		}
		void DebugLayer::onInit(Rendering::Renderer2D& renderer, Rendering::Shader& shader)
		{
			Font_Manager::get()->setScale(m_Window->getWidth() / 32.0f, m_Window->getHeight() / 18.0f);

			renderer.setRenderTarget(RenderTarget::SCREEN);
			for (int i = 0; i < 5; i++)
			{
				float y = -9.0f + i * 1.7f;
				add(new Sprite(-16, y, 6, 1.5f, 0x7f7f7f7f));
				add(new Label(String("Item ") + std::to_string(i + 1), -16.0f + 0.2f, y + 0.4f, 0xffffffff));
			}
		}
		void DebugLayer::onTick()
		{
		}
		void DebugLayer::onUpdate()
		{
		}
		void DebugLayer::onEvent()
		{
			if (Control_Manager::isKeyPressed(GLFW_KEY_LEFT_CONTROL) 
				&& Control_Manager::isKeyTyped(GLFW_KEY_TAB))
			{
				setVisible(!b_IsVisible);
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
		}
	}
}