#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

namespace Core {

	namespace Init {

		struct FramebufferInfo {

			unsigned int flags;
			bool msaa;

			FramebufferInfo() {
				// flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
				msaa = false;
			};

			FramebufferInfo(bool color, bool depth, bool stencil, bool inMsaa) {
				/* flags = GLUT_DOUBLE;
				if (color)
					flags |= GLUT_RGBA | GLUT_ALPHA;
				if (depth)
					flags |= GLUT_DEPTH;
				if (stencil)
					flags |= GLUT_MULTISAMPLE;
				if (inMsaa)
					msaa = inMsaa;
				else msaa = false; */
			}

			FramebufferInfo(const FramebufferInfo& FBO) {
				flags = FBO.flags;
				msaa = FBO.msaa;
			}

			~FramebufferInfo() {

			}

			void operator=(const FramebufferInfo& FBO) {
				flags = FBO.flags;
				msaa = FBO.msaa;
			}

		};

	}

}