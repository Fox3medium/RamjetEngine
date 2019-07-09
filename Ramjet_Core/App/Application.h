#pragma once

#include "../Core/Utils/Log.h"
#include "2DEngine.h"

namespace App {

	class Application {

	public:
		Core::Init::Window* window;
	private:
		bool m_Running, m_Suspended;
		Timer* m_Timer;
		unsigned int m_Fps, m_UpdatePerSec;

		const char* m_Name;
		uint m_Width, m_Height;

	public:

		Application(const char* name, uint width, uint height, bool fullscreen = false);
		virtual ~Application();

		// Run to initialize the engine
		virtual void init();
		// Run every second
		virtual void tick();
		// Run 60 times per second
		virtual void update();
		// Run as fast as possible
		virtual void render();

		void start();
		void suspend();
		void resume();
		void stop();

		const unsigned int getFPS() const { return m_Fps; }
		const unsigned int getUPS() const { return  m_UpdatePerSec; }

	private:
		void run();

	};

}