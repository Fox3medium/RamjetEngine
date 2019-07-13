#pragma once

#include <CoreBasicInclude.h>

#include <Core/Common.h>

#include "../Audio/Sound.h"


struct gau_Manager;
struct ga_Mixer;

namespace Core {
	
	using namespace Audio;

	namespace Manager {
		
		class CORE_API Sound_Manager 
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