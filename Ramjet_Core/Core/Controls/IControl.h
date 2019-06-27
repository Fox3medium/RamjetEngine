#pragma once

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

namespace Core {

	namespace Controls {

		class IControl {

		public:

			virtual ~IControl();

			virtual void notifyKeyPress(GLFWwindow* activeWin, float deltaTime) = 0;
			virtual void notifyMouseInput(double xpos, double ypos, float deltaTime) = 0;
			virtual void notifyScrollInput(double xoffset, double yoffset, float deltaTime) = 0;
			virtual void notifyReshape(int width, int height) = 0;
			virtual void notifyGameStart() = 0;
		};

		inline IControl::~IControl() {

		}

	}

}