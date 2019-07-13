#include "Layer.h"
#include <CoreBasicInclude.h>

namespace Core
{

	namespace Rendering
	{

		Layer::Layer()
			: m_Window(Core::Init::Window::getWindowClass())
		{
		}

		Layer::~Layer()
		{
		}

		void Layer::init()
		{
		}

		bool Layer::onEvent()
		{
			return false;
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