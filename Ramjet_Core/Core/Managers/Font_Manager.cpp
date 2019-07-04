#include "Font_Manager.h"

namespace Core {

	namespace Manager {

		std::map<std::string, Font*> Font_Manager::m_Fonts;

		void Font_Manager::add(Font* font)
		{
			m_Fonts[font->getName()] = font;
		}

		Font* Font_Manager::get(const std::string& name)
		{
			std::map<std::string, Font*>::iterator i = m_Fonts.find(name);
			if (i == m_Fonts.end()) {
				return m_Fonts[name];
			}
			return m_Fonts["SourceSansPro"];
		}

		Font* Font_Manager::get(const std::string& name, unsigned int size)
		{
			std::map<std::string, Font*>::iterator i = m_Fonts.find(name + std::to_string(size));
			if (i == m_Fonts.end()) {
				return m_Fonts[name+std::to_string(size)];
			}
			
			return m_Fonts["SourceSansPro"];
		}

		void Font_Manager::clean()
		{
			m_Fonts.clear();
		}

	}

}