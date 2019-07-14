#pragma once

#include <Core/Common.h>

#include <Utils/types.h>

#include <Init/Window.h>

namespace Core 
{
	namespace Rendering 
	{
		class CORE_API Layer
		{
		protected:
			Core::Init::Window* m_Window;

		public:
			Layer();
			virtual ~Layer();

			virtual void init();
			// TODO
			virtual void onEvent();
			virtual void onTick();
			virtual void onUpdate();
			virtual void onRender();

		};
	}
}