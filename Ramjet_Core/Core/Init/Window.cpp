#include "Window.h"

using namespace Utils;

namespace Core {

	namespace Init {

		/*WindowInfo Window::m_WInfo;*/
		Window* Window::s_Win = NULL;
		IListener* Window::m_listener = NULL;
		IControl* Window::m_control = NULL;
		float Window::m_deltaTime = 0.0f;
		float Window::m_last = 0;
		bool Window::b_Vsync = false;
		Maths::vec2 Window::m_MousePos;
		Maths::vec2 Window::m_OldMousePos;

		Window::Window(const char* in_name, int in_width, int in_height)
		{
			m_Name = in_name;
			m_Width = in_width;
			m_Height = in_height;
			m_Closed = false;
			b_MouseGrabbed = false;

			WindowInfo WInfo = WindowInfo(in_width, in_height);
			ContextInfo CInfo = ContextInfo();
			FramebufferInfo FInfo = FramebufferInfo();

			if (!init(WInfo, CInfo, FInfo))
				glfwTerminate();

			Font_Manager::add(new Font("SourceSansPro", "Assets/Test/SourceSansPro-Light.ttf", 12));
			s_Win = this;
		}

		Window::~Window()
		{
			Manager::Font_Manager::clean();
			Manager::Texture_Manager::clean();
			Manager::Sound_Manager::clean();
			glfwTerminate();
		}

		bool Window::init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FramebufferInfo& framebufferInfo) {

			m_WInfo = windowInfo;

			if (!glfwInit()) {
				CORE_FATAL("Failed to initialize GLFW!");
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
				m_Window = glfwCreateWindow(mode->width, mode->height, m_WInfo.name.c_str(),
					primary, // fullscreen
					NULL); // share ressources
			}
			else {
				m_Window = glfwCreateWindow(m_WInfo.width, m_WInfo.height, m_WInfo.name.c_str(),
					NULL, // fullscreen
					NULL); // share ressources
			}

			if (!m_Window) {
				CORE_FATAL("Failed to create OpenGL window.");
				return false;
			}

			glfwMakeContextCurrent(m_Window);			

			if (glewInit() != GLEW_OK) {
				CORE_FATAL("ERROR : GLEW initialize failed.");
			}

			printOpenGLInfo();

			glfwSetFramebufferSizeCallback(m_Window, windowSizeCallback);
			glfwSetWindowUserPointer(m_Window, this);

			glfwSetWindowRefreshCallback(m_Window, idleCallback);
			glfwSetCursorPosCallback(m_Window, processMouseInput);
			glfwSetScrollCallback(m_Window, processScrollInput);
			glfwSetKeyCallback(m_Window, processKeyInput);
			glfwSetMouseButtonCallback(m_Window, processMButtonInput);
			glfwSwapInterval(0.0); //Disable VSync = 0.0, Enable VSync = 1.0

			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;

		}

		void Window::printOpenGLInfo()
		{
			CORE_WARN("----------------------------------");
			CORE_WARN(" OpenGL:");
			CORE_WARN("    ", glGetString(GL_VERSION));
			CORE_WARN("    ", glGetString(GL_VENDOR));
			CORE_WARN("    ", glGetString(GL_RENDERER));
			CORE_WARN("----------------------------------");
		}
		
		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			tick();
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwSwapBuffers(m_Window);
			glfwPollEvents();

			Sleep(1);

			Manager::Sound_Manager::update();
		}

		void Window::setVsync(bool enabled)
		{
			glfwSwapInterval((double)enabled);
			b_Vsync = enabled;
		}

		void Window::setGrabMouse()
		{
			if (b_MouseGrabbed) 
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);			
			else 
				glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			b_MouseGrabbed = !b_MouseGrabbed;				
		}

		bool Window::isMouseGrabbed()
		{
			return b_MouseGrabbed;
		}

		Maths::vec2 Window::getMousePos()
		{
			Maths::vec2 result = m_MousePos - m_OldMousePos;
			m_OldMousePos = m_MousePos;
			return result;
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_Window) == 1;
		}

		int Window::getWidth() const
		{
			return m_Width;
		}

		int Window::getHeight() const
		{
			return m_Height;
		}

		Window* Window::getWindowClass()
		{
			return s_Win;
		}

		void Window::windowSizeCallback(GLFWwindow *window, int width, int height)
		{
			//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
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
			m_OldMousePos.x = m_MousePos.x;
			m_OldMousePos.y = m_MousePos.y;
			m_MousePos.x = xpos;
			m_MousePos.y = ypos;
			//m_control->notifyMouseInput(xpos, ypos, m_deltaTime);
		}

		void Window::processScrollInput(GLFWwindow* window, double xoffset, double yoffset)
		{
			m_control->notifyScrollInput(xoffset, yoffset, m_deltaTime);
		}

		void Window::tick()
		{
			float current = glfwGetTime();
			m_deltaTime = current - m_last;
			m_last = current;
		}

		void Window::setListener(IListener*& listener)
		{
		}

		void Window::setControl(Control_Manager*& control)
		{
			m_control = control;
		}

		float Window::getDeltaTime()
		{
			return m_deltaTime;
		}

		float Window::getLastTime()
		{
			return m_last;
		}

	}
}

