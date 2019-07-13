#pragma once

#include "../Controls/IControl.h"
#include <Utils/Log.h>
#include <Utils/Maths/maths.h>
#include <Sound_Manager.h>

using namespace Core::Controls;

namespace Core { 

	namespace Manager {

		#define MAX_KEYS 1024
		#define MAX_BUTTONS 32

		class Control_Manager {

		public:
			Control_Manager();
			~Control_Manager();

			static void notifyKeyPress(int keycode, int action, float deltaTime, InputType inputType);
			static void notifyMouseInput(double xpos, double ypos, float deltaTime);
			static void notifyScrollInput(double xoffset, double yoffset, float deltaTime);
			static void notifyReshape(int width, int height);
			static void notifyGameStart();

			static bool isKeyPressed(unsigned int keycode);
			static bool isKeyTyped(unsigned int keycode);

			static bool isMouseButtonPressed(unsigned int keycode);

			//static Maths::vec2 getMousePosition();

			//void update(glm::mat4& view_matrix, glm::mat4& projection_matrix, glm::vec3& cameraPosition, glm::vec3& cameraDirection);

			//void setPlayerPosition(glm::vec3 position, glm::vec3 rotation);

			//void getPlayerPosition(glm::vec3& position, glm::vec3& rotation);

			static void updateInput();

			static void setPlayerSpeed(float speed);

		private:

		private:
			//FPSCamera* playerCamera;

			//int oldWidth;
			//int oldHeight;

			static float playerSpeed;
			//float runSpeed;

			static bool gameStarted;

			static bool m_Keys[MAX_KEYS];
			static bool m_KeysState[MAX_KEYS];
			static bool m_KeysTyped[MAX_KEYS];

			static bool m_MouseButtons[MAX_BUTTONS];
			static bool m_MouseButtonsState[MAX_BUTTONS];
			static bool m_MouseButtonsTyped[MAX_BUTTONS];

			static Maths::vec2 m_MousePos;
			static double m_ScrollX, m_ScrollY;

		};

	} 
}