#pragma once

#include "../Core/Utils/Log.h"
#include "2DEngine.h"

namespace Core {

	class Core {

	protected:
		Init::Window* m_Window;
		Timer* m_Timer;
		unsigned int m_Fps, m_UpdatePerSec;

	public:
		void start() {
			init();
			run();
		}

	protected:
		Core()
			: m_Fps(0), m_UpdatePerSec(0)
		{
		}	

		virtual ~Core() 
		{
			delete m_Timer;
			delete m_Window;
		}

		// Run to initialize the engine
		virtual void init() = 0;
		// Run every second
		virtual void tick() = 0;
		// Run 60 times per second
		virtual void update() = 0;
		// Run as fast as possible
		virtual void render() = 0;

		Init::Window* createWindow(const char* name, int width, int height)
		{
			m_Window = new Init::Window(name, width, height);
			return m_Window;
		}

		const unsigned int getFPS() const { return m_Fps; }
		const unsigned int getUPS() const { return  m_UpdatePerSec; }

	private:
		void run()
		{
			m_Timer = new Timer();
			float timer = 0.0f;
			float updateTimer = 0.0f;
			float updateTick = 1.0f / 60.0f;
			unsigned int frames = 0;
			unsigned int updates = 0;
			while (!m_Window->closed())
			{
				m_Window->clear();
				if (m_Timer->elapsed() - updateTimer > updateTick)
				{
					update();
					updates++;
					updateTimer += updateTick;
				}
				render();
				frames++;
				m_Window->update();
				if (m_Timer->elapsed() - timer > 1.0f)
				{
					timer += 1.0f;
					m_Fps = frames;
					m_UpdatePerSec = updates;
					frames = 0;
					updates = 0;
					tick();
				}
			}

		}

	};

}