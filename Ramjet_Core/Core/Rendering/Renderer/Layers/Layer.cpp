#include "Layer.h"
#include <CoreBasicInclude.h>

namespace Core
{

	namespace Rendering
	{

		Layer::Layer()
			: m_Window(Core::Init::Window::getWindowClass()), b_IsVisible(true)
		{
		}

		Layer::~Layer()
		{
		}

		void Layer::init()
		{
		}

		void Layer::onEvent()
		{

		}

		void Layer::onTick()
		{
		}

		void Layer::onUpdate()
		{
		}

		void Layer::onRender()
		{
		}

	}

}