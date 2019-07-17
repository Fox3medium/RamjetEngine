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

		struct Inputs 
		{
			bool m_Keys[MAX_KEYS];
			bool m_KeysState[MAX_KEYS];
			bool m_KeysTyped[MAX_KEYS];

			bool m_MouseButtons[MAX_BUTTONS];
			bool m_MouseButtonsState[MAX_BUTTONS];
			bool m_MouseButtonsTyped[MAX_BUTTONS];

			Inputs() 
			{
				for (int i = 0; i < MAX_KEYS; i++)
				{
					m_Keys[i] = false;
					m_KeysState[i] = false;
					m_KeysTyped[i] = false;
				}

				for (int i = 0; i < MAX_BUTTONS; i++)
				{
					m_MouseButtons[i] = false;
					m_MouseButtonsState[i] = false;
					m_MouseButtonsTyped[i] = false;
				}
			}
		};

		class CORE_API Control_Manager {

		public:
			Control_Manager();
			~Control_Manager();

			static void init();

			static void notifyKeyPress(int keycode, int action, float deltaTime, InputType inputType);
			static void notifyMouseInput(double xpos, double ypos, float deltaTime);
			static void notifyScrollInput(double xoffset, double yoffset, float deltaTime);
			static void notifyReshape(int width, int height);
			static void notifyGameStart();

			static bool isKeyPressed(unsigned int keycode);
			static bool isKeyTyped(unsigned int keycode);

			static bool isMouseButtonPressed(unsigned int keycode);

			static bool isKeyEvent();

			//static Maths::vec2 getMousePosition();

			//void update(glm::mat4& view_matrix, glm::mat4& projection_matrix, glm::vec3& cameraPosition, glm::vec3& cameraDirection);

			//void setPlayerPosition(glm::vec3 position, glm::vec3 rotation);

			//void getPlayerPosition(glm::vec3& position, glm::vec3& rotation);

			static void updateInput();

			static void setPlayerSpeed(float speed);

		private:

			static int getKey(int keyCode);

		private:
			//FPSCamera* playerCamera;

			//int oldWidth;
			//int oldHeight;

			static float playerSpeed;
			//float runSpeed;

			static bool gameStarted;

			static Inputs* s_Input;

			static uint m_NumberOfKeysPressed;

			static Maths::vec2 m_MousePos;
		};

	} 
}