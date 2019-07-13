#include <CoreBasicInclude.h>
#include "InitWindow.h"
#include <Utils/Log.h>
#include <Managers/embed/Embedded.h>
#include <Managers/Font_Manager.h>
#include <Managers/Texture_Manager.h>
#include <GLEW/glew.h>


namespace Core 
{
	using namespace Manager;
	namespace Init 
	{
		std::map<void*, InitWindow*> InitWindow::s_Handles;

		InitWindow::InitWindow(const char* title, uint width, uint height)
			: m_Title(title), m_Width(width), m_Height(height), m_Handle(nullptr), m_Closed(false)
		{
			if (!init())
			{
				CORE_ERROR("Failed base Window initialization!");
				return;
			}

			Font_Manager::add(new Font("SourceSansPro", Internal::DEFAULT_FONT, Internal::DEFAULT_FONT_SIZE, 32));

			Sound_Manager::init();
			//Texture_Manager::init(); TODO

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
			m_MouseGrabbed = true;
		}

		InitWindow::~InitWindow()
		{
			Font_Manager::clean();
			Texture_Manager::clean();
			Sound_Manager::clean();
		}

		bool InitWindow::init()
		{
			if (!platformInit())
			{
				CORE_FATAL("Failed to initialize platform!");
				return false;
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			CORE_WARN("----------------------------------");
			CORE_WARN(" OpenGL:");
			CORE_WARN("    ", glGetString(GL_VERSION));
			CORE_WARN("    ", glGetString(GL_VENDOR));
			CORE_WARN("    ", glGetString(GL_RENDERER));
			CORE_WARN("----------------------------------");
			return true;
		}

		bool InitWindow::isKeyPressed(uint keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_Keys[keycode];
		}

		bool InitWindow::isKeyTyped(uint keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyTyped[keycode];
		}

		bool InitWindow::isMouseButtonPressed(uint button) const
		{
			// TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		bool InitWindow::isMouseButtonClicked(uint button) const
		{
			// TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseClicked[button];
		}

		const Maths::vec2& InitWindow::getMousePosition() const
		{
			return m_MousePosition;
		}

		const bool InitWindow::isMouseGrabbed() const
		{
			return m_MouseGrabbed;
		}

		void InitWindow::setMouseGrabbed(bool grabbed)
		{
			m_MouseGrabbed = grabbed;
		}

		void InitWindow::setVsync(bool enabled)
		{
			// TODO: Not implemented
			m_Vsync = enabled;
		}

		void InitWindow::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void InitWindow::update()
		{
			platformUpdate();
			Sound_Manager::update();
		}

		void InitWindow::updateInput()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				m_KeyTyped[i] = m_Keys[i] && !m_KeyState[i];

			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

			memcpy(m_KeyState, m_Keys, MAX_KEYS);
			memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
		}

		bool InitWindow::closed() const
		{
			return m_Closed;
		}

		void InitWindow::registerWindowClass(void* handle, InitWindow* window)
		{
			s_Handles[handle] = window;
		}

		InitWindow* InitWindow::getWindowClass(void* handle)
		{
			if (handle == nullptr)
				return s_Handles.begin()->second;

			return s_Handles[handle];
		}
	}
}