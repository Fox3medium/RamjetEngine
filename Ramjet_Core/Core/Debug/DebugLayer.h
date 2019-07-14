#pragma once

#include <Rendering/Renderer/Renderer2D.h>
#include <Rendering/Renderer/Layers/Layer2D.h>
#include <Rendering/Renderer/Shader/Shader.h>

// TODO DEBUG Events => CONTROL MANAGER

namespace Core 
{
	namespace Debug 
	{
		class DebugLayer : public Rendering::Layer2D
		{
		private:

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