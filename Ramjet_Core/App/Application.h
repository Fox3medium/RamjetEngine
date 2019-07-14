#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>

#include <Utils/types.h>

#include <Init/Window.h>
#include <Managers/Control_Manager.h>

#include <Rendering/Renderer/Layers/Layer.h>
#include <Utils/Timer.h>

namespace Core 
{
	namespace Debug
	{ 
		class DebugLayer;
	}
}


namespace App {

	using namespace Core::Rendering;

	class CORE_API Application {

	public:
		Core::Init::Window* window;
		Core::Manager::Control_Manager* C_Manager;

		Core::Debug::DebugLayer* m_DebugLayer;

	private:
		static Application* s_Instance;

		bool m_Running, m_Suspended;
		Timer* m_Timer;
		unsigned int m_Fps, m_UpdatePerSec;

		const char* m_Name;
		uint m_Width, m_Height;

		std::vector<Layer*> m_Layers;
		std::vector<Layer*> m_OverlayStack;

	public:

		Application(const char* name, uint width, uint height, bool fullscreen = false);
		virtual ~Application();

		void pushLayer(Layer* layer);
		Layer* popLayer();

		void pushOverlay(Layer* layer);
		Layer* popOverlay();

		// Run to initialize the engine
		virtual void init();
		// Run every second
		void tick();
		// Run 60 times per second
		void update();
		// Run as fast as possible
		void render();

		void onEvent();

		void start();
		void suspend();
		void resume();
		void stop();

		const uint getFPS() const { return m_Fps; }
		const uint getUPS() const { return  m_UpdatePerSec; }

		inline static Application& getApplication() { return *s_Instance; }

	private:
		void platformInit();
		void run();

	};

}