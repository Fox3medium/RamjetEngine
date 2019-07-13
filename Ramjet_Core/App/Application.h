#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>

#include <map>

#include "../Core/Utils/Log.h"
#include "2DEngine.h"

#include <Rendering/Renderer/Layers/Layer.h>
#include <Utils/Timer.h>

namespace App {

	using namespace Core::Rendering;

	class CORE_API Application {

	public:
		Core::Init::Window* window;
		Core::Manager::Control_Manager* C_Manager;

	private:
		static Application* s_Instance;

		bool m_Running, m_Suspended;
		Timer* m_Timer;
		unsigned int m_Fps, m_UpdatePerSec;

		const char* m_Name;
		uint m_Width, m_Height;

		std::vector<Layer*> m_Layers;

	public:

		Application(const char* name, uint width, uint height, bool fullscreen = false);
		virtual ~Application();

		void pushLayer(Layer* layer);
		Layer* popLayer();

		// Run to initialize the engine
		virtual void init();
		// Run every second
		void tick();
		// Run 60 times per second
		void update();
		// Run as fast as possible
		void render();

		void start();
		void suspend();
		void resume();
		void stop();

		const unsigned int getFPS() const { return m_Fps; }
		const unsigned int getUPS() const { return  m_UpdatePerSec; }

		inline static Application& getApplication() { return *s_Instance; }

	private:
		void run();

	};

}