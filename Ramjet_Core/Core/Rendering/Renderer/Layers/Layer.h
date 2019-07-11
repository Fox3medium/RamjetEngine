#pragma once

#include <Utils/types.h>

#include <Init/Window.h>

namespace Core 
{
	namespace Rendering 
	{
		class Layer
		{
		protected:
			Core::Init::Window* m_Window;

		public:
			Layer();
			virtual ~Layer();

			virtual void init();
			// TODO
			virtual bool onEvent();
			virtual void onTick();
			virtual void onUpdate();
			virtual void onRender();

		};
	}
}