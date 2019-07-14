#pragma once

#include <Rendering/Renderer/Renderer2D.h>
#include <Rendering/Renderer/Layers/Layer2D.h>
#include <Rendering/Renderer/Shader/Shader.h>

#include <Rendering/Renderer/Models/Label.h>
#include <Rendering/Renderer/Models/Sprite.h>
#include "DebugMenu.h"

// TODO DEBUG Events => CONTROL MANAGER

namespace App 
{
	class Application;
}

namespace Core 
{
	namespace Debug 
	{
		class CORE_API DebugLayer : public Rendering::Layer2D
		{
		private:
			App::Application& m_Application;
			Rendering::Label* m_FPSLabel;
		public:
			DebugLayer();
			~DebugLayer();

			void onInit(Rendering::Renderer2D& renderer, Rendering::Shader& shader) override;


			void onTick() override;
			void onUpdate() override;

			void onEvent() override;
			bool onMouseMovedEvent();
			bool onKeyPressedEvent();

			void onRender(Rendering::Renderer2D& renderer) override;
		};
	}
}