#pragma once

#include <map>

#include "../Audio/Sound.h"

#define GAU_THREAD_POLICY_MULTI		2
#include <gorilla-audio/ga.h>
#include <gorilla-audio/gau.h>

namespace Core {
	
	using namespace Audio;

	namespace Manager {
		
		class Sound_Manager 
		{
		private:
			friend class Sound;

			static gau_Manager* m_Manager;
			static ga_Mixer* m_Mixer;

			static std::map<String, Sound*> m_Sounds;

		public:
			static void init();
			static void add(Sound* sound);
			static Sound* get(const String& name);
			static void update();
			static void clean();

		private:
			Sound_Manager() {}
		};

	}

}