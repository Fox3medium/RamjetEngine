#pragma once

#include "Sound.h"
#include <Managers/Sound_Manager.h>

using namespace Core::Manager;

namespace Core {

	namespace Audio {

		Sound::Sound(const String& name, const String& filename)
			: m_Name(name), m_FileName(filename), b_Playing(false), m_Count(0)
		{
			std::vector<String> split = Utils::SplitString(m_FileName, '.');
			if (split.size() < 2) {
				std::cout << "[SOUND] Invalid file name " << m_FileName << "!" << std::endl;
				return;
			}
			m_Sound = gau_load_sound_file(filename.c_str(), split.back().c_str());

			if (m_Sound == nullptr)
				std::cout << "[SOUND] Could not load file " << m_FileName << "!" << std::endl;

			m_Gain = 0.5f;
		}

		Sound::~Sound()
		{
			ga_sound_release(m_Sound);
		}

		void destroy_on_finish(ga_Handle* in_Handle, void* in_context)
		{
			Sound* sound = (Sound*)in_Handle->sound;
			sound->m_Count--;
			if(sound->m_Count == 0)
				sound->stop();
			// ga_handle_destroy(in_Handle);
		}

		void loop_on_finish(ga_Handle* in_Handle, void* in_context)
		{
			Sound* sound = (Sound*)in_Handle->sound;
			sound->loop();
			ga_handle_destroy(in_Handle);
		}

		void Sound::play()
		{
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(Sound_Manager::m_Mixer, m_Sound, &destroy_on_finish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
			b_Playing = true;
			setGain(m_Gain);
			m_Count++;
		}

		void Sound::loop()
		{
			gc_int32 quit = 0;
			m_Handle = gau_create_handle_sound(Sound_Manager::m_Mixer, m_Sound, &loop_on_finish, &quit, NULL);
			m_Handle->sound = this;
			ga_handle_play(m_Handle);
			b_Playing = true;
		}

		void Sound::pause()
		{
			if (!b_Playing)
				return;
			b_Playing = false;
			ga_handle_stop(m_Handle);
		}

		void Sound::resume()
		{
			if (b_Playing)
				return;
			gc_int32 quit = 0;
			ga_handle_play(m_Handle);
			b_Playing = true;
		}

		void Sound::stop()
		{
			if (!b_Playing)
				return;

			ga_handle_stop(m_Handle);
			b_Playing = false;
		}

		void Sound::setGain(float gain)
		{
			if (!b_Playing) 
			{
				std::cout << "[SOUND] Cannot set gain! No sound are currently playing." << std::endl;
				return;
			}
			m_Gain += gain;
			ga_handle_setParamf(m_Handle, GA_HANDLE_PARAM_GAIN, m_Gain);
		}


	}

}