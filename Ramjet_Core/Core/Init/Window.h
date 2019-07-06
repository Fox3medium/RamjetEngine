#pragma once

// OpenGL
#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

// Listener
#include "../Controls/IControl.h" // Listener
#include "../Managers/Control_Manager.h" // Linked Manager
#include "../Managers/Sound_Manager.h"
#include "../Managers/Font_Manager.h"
#include "../Managers/Texture_Manager.h"

// Utilities
//#include <Utils/String.h>
#include <Utils/Static/CInOut.h>

// Other
#include "ContextInfo.h"
#include "DebugOutput.h"
#include "FramebufferInfo.h"
#include "IListener.h"
#include "WindowInfo.h"



namespace Core {

	using namespace Manager;
	using namespace Controls;

	namespace Init{

		class Window
		{
			public:

				/*
				* Constructor
				*/
				Window(const char* in_name, int in_width, int in_height);

				/*
				* Destructor
				*/
				~Window();

				void clear() const;

				/*
				* Update
				*/
				void update();

				bool closed() const;

				int getWidth() const;

				int getHeight() const;



			protected :

				bool init(const WindowInfo& windowInfo, const ContextInfo& contextInfo, const FramebufferInfo& framebufferInfo);

				static void printOpenGLInfo(const WindowInfo& WInfo, const ContextInfo& CInfo);

				// CALLBACKS
				static void windowSizeCallback(GLFWwindow* window, int width, int height);
				static void idleCallback(GLFWwindow* window);
				static void closeCallBack();
				static void displayCallback(void);

				// INPUT CALLBACK
				static void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void processMButtonInput(GLFWwindow* window, int button, int action, int mods);
				static void processMouseInput(GLFWwindow* window, double xpos, double ypos);
				static void processScrollInput(GLFWwindow* window, double xoffset, double yoffset);

				static void tick();

			public :

				//LISTENER FUNCTIONS
				static void setListener(IListener*& listener);
				static void setControl(Control_Manager*& control);

				static float getDeltaTime();
				static float getLastTime();

			private:

				static IControl* m_control;

				static IListener* m_listener;

				static float m_deltaTime;
				static float m_last;



				/*
				* Windows Name
				*/
				const char* m_Name;

				/*
				* Windows Size
				*/
				int m_Width, m_Height;

				bool m_Closed;

				/*
				* Active Window
				*/
				GLFWwindow* m_Window;
				WindowInfo m_WInfo;

		};
	}
}


