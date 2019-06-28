#pragma once

#include "../Controls/IControl.h"
#include <Utils/Static/CInOut.h>
#include <Utils/Maths/maths.h>

using namespace Core::Controls;

namespace Core { 

	namespace Manager {

		#define MAX_KEYS 1024
		#define MAX_BUTTONS 32

		class Control_Manager : public IControl {

		public:
			Control_Manager();
			~Control_Manager();

			virtual void notifyKeyPress(GLFWwindow* activeWin, float deltaTime);
			virtual void notifyMouseInput(double xpos, double ypos, float deltaTime);
			virtual void notifyScrollInput(double xoffset, double yoffset, float deltaTime);
			virtual void notifyReshape(int width, int height);
			virtual void notifyGameStart();

			static bool isKeyPressed(unsigned int keycode);

			void getMousePosition(double& x, double& y) const;

			//void update(glm::mat4& view_matrix, glm::mat4& projection_matrix, glm::vec3& cameraPosition, glm::vec3& cameraDirection);

			//void setPlayerPosition(glm::vec3 position, glm::vec3 rotation);

			//void getPlayerPosition(glm::vec3& position, glm::vec3& rotation);

			void setPlayerSpeed(float speed);

		private:
			//FPSCamera* playerCamera;

			int oldWidth;
			int oldHeight;

			float playerSpeed;
			float runSpeed;

			bool gameStarted;

			static bool m_keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];

			static double m_MouseX, m_MouseY;
			static double m_ScrollX, m_ScrollY;

		};

	} 
}