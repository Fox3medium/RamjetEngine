#pragma once

#include <GLEW/glew.h>
#include <Utils/Maths/maths.h>
#include "Renderable2D.h"

namespace Core {

	namespace Rendering {
	
		class Renderer2D
		{
		protected:
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void flush() = 0;
		};

	}

}


