#include "Control_Manager.h"

using namespace Utils;

namespace Core {

	namespace Manager {
		
		double Control_Manager::m_MouseX;
		double Control_Manager::m_MouseY;
		double Control_Manager::m_ScrollX;
		double Control_Manager::m_ScrollY;

		Control_Manager::Control_Manager()
		{
			playerSpeed = 2.5f;
			gameStarted = false;
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
			if (glfwGetKey(activeWin, GLFW_KEY_D) == GLFW_PRESS)
				CInOut::Out("YOU PRESS D");
			if (glfwGetKey(activeWin, GLFW_KEY_A) == GLFW_PRESS)
				CInOut::Out("YOU PRESS A");
			if (glfwGetKey(activeWin, GLFW_KEY_W) == GLFW_PRESS)
				CInOut::Out("YOU PRESS W");
			if (glfwGetKey(activeWin, GLFW_KEY_S) == GLFW_PRESS)
				CInOut::Out("YOU PRESS S");
			if (glfwGetKey(activeWin, GLFW_KEY_E) == GLFW_PRESS)
				CInOut::Out("YOU PRESS E");
			if (glfwGetKey(activeWin, GLFW_KEY_Q) == GLFW_PRESS)
				CInOut::Out("YOU PRESS Q");
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
			if (glfwGetKey(activeWin, GLFW_KEY_S) == GLFW_PRESS)
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
			return true;
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