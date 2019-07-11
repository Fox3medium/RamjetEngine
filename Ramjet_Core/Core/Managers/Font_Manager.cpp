#include "Font_Manager.h"
#include "embed/Embedded.h"

namespace Core {

	namespace Manager {

		std::map<std::string, Font*> Font_Manager::m_Fonts;

		void Font_Manager::init()
		{
			add(new Font("SourceSansPro", Core::Internal::DEFAULT_FONT, Core::Internal::DEFAULT_FONT_SIZE, 24));
		}

		void Font_Manager::add(Font* font)
		{
			m_Fonts[font->getName()] = font;
		}

		Font* Font_Manager::get()
		{
			return  m_Fonts["SourceSansPro"];
		}

		Font* Font_Manager::get(const std::string& name)
		{
			std::map<std::string, Font*>::iterator i = m_Fonts.find(name);
			if (i != m_Fonts.end()) {
				return m_Fonts[name];
			}
			return m_Fonts["SourceSansPro"];
		}

		Font* Font_Manager::get(const std::string& name, unsigned int size)
		{
			std::string n = name + std::to_string(size);
			std::map<std::string, Font*>::iterator i = m_Fonts.find(n);
			if (i != m_Fonts.end()) {
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