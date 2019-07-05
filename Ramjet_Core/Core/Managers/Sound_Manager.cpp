#pragma once

#include "Sound_Manager.h"

namespace Core {

	namespace Manager {

		gau_Manager* Sound_Manager::m_Manager = nullptr;
		ga_Mixer* Sound_Manager::m_Mixer = nullptr;
		std::map<std::string, Sound*> Sound_Manager::m_Sounds;

		void Sound_Manager::init()
		{
			gc_initialize(0);
			m_Manager = gau_manager_create();
			m_Mixer = gau_manager_mixer(m_Manager);
		}

		void Sound_Manager::add(Sound* sound)
		{
			m_Sounds[sound->getName()] = sound;
			//return sound;
		}

		Sound* Sound_Manager::get(const std::string& name)
		{
			std::map<std::string, Sound*>::iterator i = m_Sounds.find(name);
			if (i != m_Sounds.end()) {
				return m_Sounds[name];
			}
			// TODO RETURN DEFAULT
			return nullptr;
		}

		void Sound_Manager::update()
		{
			gau_manager_update(m_Manager);
		}

		void Sound_Manager::clean()
		{
			if (!m_Sounds.empty()) {
				gau_manager_destroy(m_Manager);
				gc_shutdown();
				m_Sounds.clear();
			}
			
		}

	}

}