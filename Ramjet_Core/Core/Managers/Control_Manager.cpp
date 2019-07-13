#include "Control_Manager.h"

using namespace Utils;

namespace Core {

	namespace Manager {
		
		Maths::vec2 Control_Manager::m_MousePos;
		float Control_Manager::playerSpeed = 0.0f;
		bool Control_Manager::gameStarted = false;
		double Control_Manager::m_ScrollX;
		double Control_Manager::m_ScrollY;
		bool Control_Manager::m_Keys[MAX_KEYS];
		bool Control_Manager::m_KeysState[MAX_KEYS];
		bool Control_Manager::m_KeysTyped[MAX_KEYS];
		bool Control_Manager::m_MouseButtons[MAX_BUTTONS];
		bool Control_Manager::m_MouseButtonsTyped[MAX_BUTTONS];
		bool Control_Manager::m_MouseButtonsState[MAX_BUTTONS];

		Control_Manager::Control_Manager()
		{
			playerSpeed = 2.5f;
			gameStarted = false;

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

			//playerCamera = new FPSCamera();
		}

		Control_Manager::~Control_Manager()
		{
		}

		void Control_Manager::notifyKeyPress(int keycode, int action, float deltaTime, InputType inputType)
		{
			playerSpeed = 2.5f * deltaTime;

			if (inputType == InputType::KEYBOARD)
			{
				m_Keys[keycode] = action != GLFW_RELEASE;
			} 
			else if (inputType == InputType::MOUSE)
			{
				m_MouseButtons[keycode] = action != GLFW_RELEASE;
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
			return m_Keys[keycode];
		}

		bool Control_Manager::isKeyTyped(unsigned int keycode)
		{
			return m_KeysTyped[keycode];
		}

		bool Control_Manager::isMouseButtonPressed(unsigned int keycode)
		{
			return m_MouseButtons[keycode];
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

		void Control_Manager::updateInput()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				m_KeysTyped[i] = m_Keys[i] && !m_KeysState[i];

			memcpy(m_KeysState, m_Keys, MAX_KEYS);

			for (int i = 0; i < MAX_KEYS; i++)
				m_MouseButtonsTyped[i] = m_MouseButtons[i] && !m_MouseButtonsState[i];

			memcpy(m_MouseButtonsState, m_MouseButtons, MAX_BUTTONS);
		}

	}
}