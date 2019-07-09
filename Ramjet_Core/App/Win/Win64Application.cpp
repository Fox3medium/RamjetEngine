#include <App/Application.h>

namespace App 
{

	Application::Application(const char* name, uint width, uint height, bool fullscreen)
		: m_Name(name), m_Width(width), m_Height(height)
	{
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::init()
	{
		window = new Core::Init::Window(m_Name, m_Width, m_Height);
	}

	void Application::start()
	{
		init();
		m_Running = true;
		m_Suspended = false;
		run();
	}

	void Application::suspend()
	{
		m_Suspended = true;
	}

	void Application::resume()
	{
		m_Suspended = false;
	}

	void Application::stop()
	{
		m_Running = false;
	}

	void Application::tick()
	{

	}

	void Application::update()
	{

	}

	void Application::render()
	{

	}

	void Application::run()
	{
		m_Timer = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (m_Running)
		{
			window->clear();
			if (m_Timer->elapsed() - updateTimer > updateTick)
			{
				update();
				updates++;
				updateTimer += updateTick;
			}
			render();
			frames++;
			window->update();
			if (m_Timer->elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_Fps = frames;
				m_UpdatePerSec = updates;
				frames = 0;
				updates = 0;
				tick();
			}
			if (window->closed())
				m_Running = false;
		}
	}
}