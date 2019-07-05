#include "Texture_Manager.h"

namespace Core {

	namespace Manager {

		std::map<String, Texture* > Texture_Manager::m_Textures;

		void Texture_Manager::add(Texture* texture)
		{
			m_Textures[texture->getName()] = texture;
		}

		Texture* Texture_Manager::get(const String& name)
		{
			std::map<String, Texture* >::iterator i = m_Textures.find(name);
			if (i != m_Textures.end()) {
				return m_Textures[name];
			}
			// TODO RETURN DEFAULT
			return nullptr;
		}

		void Texture_Manager::clean()
		{
			m_Textures.clear();
		}

	}

}