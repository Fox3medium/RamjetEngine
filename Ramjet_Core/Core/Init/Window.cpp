#include "Window.h"

using namespace Utils;

namespace Core {

	namespace Init {

		/*WindowInfo Window::m_WInfo;
		GLFWwindow* Window::m_Window;*/
		IListener* Window::m_listener = NULL;
		IControl* Window::m_control = NULL;
		float Window::m_deltaTime = 0;
		float Window::m_last = 0;

		Window::Window(const char* in_name, int in_width, int in_height)
		{
			m_Name = in_name;
			m_Width = in_width;
			m_Height = in_height;
			m_Closed = false;

			WindowInfo WInfo = WindowInfo();
			ContextInfo CInfo = ContextInfo();
			FramebufferInfo FInfo = FramebufferInfo();

			if (!init(WInfo, CInfo, FInfo))
				glfwTerminate();
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FramebufferInfo& framebufferInfo) {

			m_WInfo = windowInfo;

			if (!glfwInit()) {
				CInOut::Out("ERROR : GLFW Failed to initialize.");
				return false;
			}

			/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextInfo.major_version);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextInfo.minor_version);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

			if (m_WInfo.bisFullscreen) {
				GLFWmonitor* primary = glfwGetPrimaryMonitor();
				const GLFWvidmode* mode = glfwGetVideoMode(primary);
				m_WInfo.height = mode->height;
				m_WInfo.width = mode->width;
				m_Window = glfwCreateWindow(mode->width, mode->height, m_WInfo.name,
					primary, // fullscreen
					NULL); // share ressources
			}
			else {
				m_Window = glfwCreateWindow(m_WInfo.width, m_WInfo.height, m_WInfo.name,
					NULL, // fullscreen
					NULL); // share ressources
			}

			if (!m_Window) {
				CInOut::Out("ERROR : Failed to create OpenGL window.");
				return false;
			}

			glfwMakeContextCurrent(m_Window);			

			if (glewInit() != GLEW_OK) {
				CInOut::Out("ERROR : GLEW initialize failed.");
			}

			std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;

			glfwSetWindowSizeCallback(m_Window, windowSizeCallback);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowRefreshCallback(m_Window, idleCallback);
			glfwSetCursorPosCallback(m_Window, processMouseInput);
			glfwSetScrollCallback(m_Window, processScrollInput);
			glfwSetKeyCallback(m_Window, processKeyInput);
			glfwSetMouseButtonCallback(m_Window, processMButtonInput);

			return true;

		}

		void Window::printOpenGLInfo(const WindowInfo& WInfo, const ContextInfo& CInfo)
		{
		}
		
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window);
		}

		int Window::getWidth() const
		{
			return m_Width;
		}

		int Window::getHeight() const
		{
			return m_Height;
		}

		void Window::windowSizeCallback(GLFWwindow *window, int width, int height)
		{
			//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glViewport(0, 0, width, height);
		}

		void Window::idleCallback(GLFWwindow* window)
		{
		}

		void Window::closeCallBack()
		{
		}

		void Window::displayCallback(void)
		{
		}

		void Window::processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			//Window* win = (Window*) glfwGetWindowUserPointer(window);
			m_control->notifyKeyPress(window, m_deltaTime);
		}

		void Window::processMButtonInput(GLFWwindow* window, int button, int action, int mods)
		{
			m_control->notifyKeyPress(window, m_deltaTime);
		}

		void Window::processMouseInput(GLFWwindow* window, double xpos, double ypos)
		{
			m_control->notifyMouseInput(xpos, ypos, m_deltaTime);
		}

		void Window::processScrollInput(GLFWwindow* window, double xoffset, double yoffset)
		{
			m_control->notifyScrollInput(xoffset, yoffset, m_deltaTime);
		}

		void Window::tick()
		{
		}

		void Window::setListener(IListener*& listener)
		{
		}

		void Window::setControl(Control_Manager*& control)
		{
			m_control = control;
		}

	}
}

