#include "Control_Manager.h"

using namespace Utils;

namespace Core {

	namespace Manager {
		
		Maths::vec2 Control_Manager::m_MousePos;
		float Control_Manager::playerSpeed = 0.0f;
		bool Control_Manager::gameStarted = false;
		uint Control_Manager::m_NumberOfKeysPressed = 0;
		Inputs* Control_Manager::s_Input = new Inputs();

		Control_Manager::Control_Manager()
		{
			init();
		}

		Control_Manager::~Control_Manager()
		{
		}

		void Control_Manager::init()
		{
			playerSpeed = 2.5f;
			gameStarted = false;

			/*for (int i = 0; i < MAX_KEYS; i++)
			{
				s_Input->m_Keys[i] = false;
				s_Input->m_KeysState[i] = false;
				s_Input->m_KeysTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				s_Input->m_MouseButtons[i] = false;
				s_Input->m_MouseButtonsState[i] = false;
				s_Input->m_MouseButtonsTyped[i] = false;
			}*/
		}

		void Control_Manager::notifyKeyPress(int keycode, int action, float deltaTime, InputType inputType)
		{
			playerSpeed = 2.5f * deltaTime;

			if(action != GLFW_RELEASE) 
			{
				if(!s_Input->m_Keys[keycode])
				{
					m_NumberOfKeysPressed++;
				}
			} else 
			{
				m_NumberOfKeysPressed--;
			}

			if (inputType == InputType::KEYBOARD)
			{
				s_Input->m_Keys[keycode] = action != GLFW_RELEASE;
			} 
			else if (inputType == InputType::MOUSE)
			{
				s_Input->m_MouseButtons[keycode] = action != GLFW_RELEASE;
			}
			else if (inputType == InputType::JOYSTICK)
			{
				// TODO
			}
		}

		void Control_Manager::notifyMouseInput(double xpos, double ypos, float deltaTime)
		{
			m_MousePos.x = xpos;
			m_MousePos.y = ypos;
			//playerCamera->mouseInput(xpos, ypos, deltaTime);
			//std::cout << "x : " << xpos << " y : " << ypos << std::endl;
		}

		void Control_Manager::notifyScrollInput(double xoffset, double yoffset, float deltaTime)
		{
			//playerCamera->scrollInput(xoffset, yoffset, deltaTime);
			//std::cout << "x : " << xoffset << " y : " << yoffset << std::endl;
		}

		void Control_Manager::notifyReshape(int width, int height)
		{
			//playerCamera->setResolution(width, height);
		}

		void Control_Manager::notifyGameStart()
		{
			gameStarted = true;
			//playerCamera->update();
		}

		bool Control_Manager::isKeyPressed(unsigned int keycode)
		{
			int scanCode = getKey(keycode);
			return s_Input->m_Keys[scanCode];
		}

		bool Control_Manager::isKeyTyped(unsigned int keycode)
		{
			int scanCode = getKey(keycode);
			return s_Input->m_KeysTyped[scanCode];
		}

		bool Control_Manager::isMouseButtonPressed(unsigned int keycode)
		{
			return s_Input->m_MouseButtons[keycode];
		}

		bool Control_Manager::isKeyEvent()
		{
			// TODO STATIC SOLUTION
			return m_NumberOfKeysPressed != 0;
			// return true;
		}

		/*Maths::vec2 Control_Manager::getMousePosition()
		{
			return m_MousePos;
		}*/

		/*void Control_Manager::update(glm::mat4& view_matrix, glm::mat4& projection_matrix, glm::vec3& cameraPosition, glm::vec3& cameraDirection)
		{
			if (gameStarted) {
				playerCamera->getViewAndProjectionMatrix(view_matrix, projection_matrix);
				cameraPosition = playerCamera->getPlayerPosition();
				cameraDirection = playerCamera->getPlayerDirection();
			}

		}

		void Control_Manager::setPlayerPosition(glm::vec3 position, glm::vec3 rotation)
		{
			playerCamera->setPositionAndRotation(position, rotation);
		}

		void Control_Manager::getPlayerPosition(glm::vec3& position, glm::vec3& rotation)
		{
			playerCamera->getPlayerPositionAndRotation(position, rotation);
		}*/

		void Control_Manager::setPlayerSpeed(float speed)
		{
			playerSpeed = speed;
		}

		int Control_Manager::getKey(int keyCode)
		{
			int key = glfwGetKeyScancode(keyCode);
			return key;
		}

		void Control_Manager::updateInput()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				s_Input->m_KeysTyped[i] = s_Input->m_Keys[i] && !s_Input->m_KeysState[i];				

			memcpy(s_Input->m_KeysState, s_Input->m_Keys, MAX_KEYS);

			for (int i = 0; i < MAX_KEYS; i++)
				s_Input->m_MouseButtonsTyped[i] = s_Input->m_MouseButtons[i] && !s_Input->m_MouseButtonsState[i];

			memcpy(s_Input->m_MouseButtonsState, s_Input->m_MouseButtons, MAX_BUTTONS);
		}

	}
}