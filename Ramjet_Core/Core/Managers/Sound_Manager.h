#pragma once

#include <map>

#include "../Audio/Sound.h"

#define GAU_THREAD_POLICY_MULTI		2
#include <gorilla-audio/ga.h>
#include <gorilla-audio/gau.h>

using namespace Core::Audio;

namespace Core {

	namespace Manager {
		
		class Sound_Manager 
		{
		private:
			friend class Sound;

			static gau_Manager* m_Manager;
			static ga_Mixer* m_Mixer;

			static std::map<std::string, Sound*> m_Sounds;

		public:
			static void init();
			static void add(Sound* sound);
			static Sound* get(const std::string& name);
			static void update();
			static void clean();

		private:
			Sound_Manager() {}
		};

	}

}