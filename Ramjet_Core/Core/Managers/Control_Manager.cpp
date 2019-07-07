#include "Control_Manager.h"

using namespace Utils;

namespace Core {

	namespace Manager {
		
		double Control_Manager::m_MouseX;
		double Control_Manager::m_MouseY;
		double Control_Manager::m_ScrollX;
		double Control_Manager::m_ScrollY;
		bool Control_Manager::m_keys[MAX_KEYS];

		Control_Manager::Control_Manager()
		{
			playerSpeed = 2.5f;
			gameStarted = false;

			for (int i = 0; i < MAX_KEYS; i++)
				m_keys[i] = false;

			//playerCamera = new FPSCamera();
		}

		Control_Manager::~Control_Manager()
		{
		}

		void Control_Manager::notifyKeyPress(GLFWwindow* activeWin, float deltaTime)
		{
			playerSpeed = 2.5f * deltaTime;

			// KEYBOARD INPUT
			if (glfwGetKey(activeWin, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(activeWin, true);
			if (glfwGetKey(activeWin, GLFW_KEY_SPACE) == GLFW_PRESS)
				CInOut::Out("YOU PRESS SPACE BAR");
			// RIGHT
			if (glfwGetKey(activeWin, GLFW_KEY_D) == GLFW_PRESS)
			{
				m_keys[GLFW_KEY_D] = true;
			}
			else
				m_keys[GLFW_KEY_D] = false;
			// LEFT
			if (glfwGetKey(activeWin, GLFW_KEY_A) == GLFW_PRESS)
			{
				m_keys[GLFW_KEY_A] = true;
			}
			else
				m_keys[GLFW_KEY_A] = false;
			//FORWARD
			if (glfwGetKey(activeWin, GLFW_KEY_W) == GLFW_PRESS)
			{
				m_keys[GLFW_KEY_W] = true;
			}
			else
				m_keys[GLFW_KEY_W] = false;
			// BACK
			if (glfwGetKey(activeWin, GLFW_KEY_S) == GLFW_PRESS) 
			{
				m_keys[GLFW_KEY_S] = true;
			}
			else
				m_keys[GLFW_KEY_S] = false;
				

			if (glfwGetKey(activeWin, GLFW_KEY_E) == GLFW_PRESS)
			{
				m_keys[GLFW_KEY_E] = true;
			}
			else
				m_keys[GLFW_KEY_E] = false;
			if (glfwGetKey(activeWin, GLFW_KEY_Q) == GLFW_PRESS)
			{
				m_keys[GLFW_KEY_Q] = true;
			}
			else
				m_keys[GLFW_KEY_Q] = false;
			if (glfwGetKey(activeWin, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
				CInOut::Out("YOU PRESS CONTROL");
			if (glfwGetKey(activeWin, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
				CInOut::Out("YOU PRESS ALT");

			// SOUND MANAGER TEST 
			if (glfwGetKey(activeWin, GLFW_KEY_P) == GLFW_PRESS)
				Sound_Manager::get("test")->play();
			if (glfwGetKey(activeWin, GLFW_KEY_L) == GLFW_PRESS)
				Sound_Manager::get("test")->loop();
			if (glfwGetKey(activeWin, GLFW_KEY_O) == GLFW_PRESS)
				Sound_Manager::get("test")->pause();
			if (glfwGetKey(activeWin, GLFW_KEY_I) == GLFW_PRESS)
				Sound_Manager::get("test")->resume();
			if (glfwGetKey(activeWin, GLFW_KEY_U) == GLFW_PRESS)
				Sound_Manager::get("test")->stop();

			if (glfwGetKey(activeWin, GLFW_KEY_UP) == GLFW_PRESS) 
			{
				Sound_Manager::get("test")->setGain(0.05f);				
			}
				

			if (glfwGetKey(activeWin, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				Sound_Manager::get("test")->setGain(-0.05f);
			}


			// MOUSE INPUT
			if (glfwGetMouseButton(activeWin, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
				CInOut::Out("YOU PRESS MB1");
		}

		void Control_Manager::notifyMouseInput(double xpos, double ypos, float deltaTime)
		{
			m_MouseX = xpos;
			m_MouseY = ypos;
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
			return m_keys[keycode];
		}

		void Control_Manager::getMousePosition(double& x, double& y) const
		{
			x = m_MouseX;
			y = m_MouseY;
		}

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

	}
}