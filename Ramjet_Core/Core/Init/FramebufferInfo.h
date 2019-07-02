#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace Core {

	namespace Init {

		struct FramebufferInfo {

			bool msaa;

			FramebufferInfo() {
				msaa = false;
			};

			FramebufferInfo(const FramebufferInfo& FBO) {
				msaa = FBO.msaa;
			}

			~FramebufferInfo() {

			}

			void operator=(const FramebufferInfo& FBO) {
				msaa = FBO.msaa;
			}

		};

	}

}