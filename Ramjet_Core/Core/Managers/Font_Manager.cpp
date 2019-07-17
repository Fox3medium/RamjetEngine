#include <Core/CoreBasicInclude.h>
#include "Font_Manager.h"
#include "embed/Embedded.h"

namespace Core {

	namespace Manager {

		std::map<String, Font*> Font_Manager::m_Fonts;
		Maths::vec2 Font_Manager::s_Scale;

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

		Font* Font_Manager::get(const String& name)
		{
			std::map<String, Font*>::iterator i = m_Fonts.find(name);
			if (i != m_Fonts.end()) {
				return m_Fonts[name];
			}
			return m_Fonts["SourceSansPro"];
		}

		Font* Font_Manager::get(const String& name, unsigned int size)
		{
			String n = name + std::to_string(size);
			std::map<String, Font*>::iterator i = m_Fonts.find(n);
			if (i != m_Fonts.end()) {
				return m_Fonts[name+std::to_string(size)];
			}
			
			return m_Fonts["SourceSansPro"];
		}

		Font* Font_Manager::get(uint size)
		{
			// TODO
			/*for (Font* font : s_Fonts)
			{
				if (font->GetSize() == size)
					return font;
			}
			Font* result = new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, size);
			result->SetScale(s_Scale);
			Add(result);
			return result;*/
			return nullptr;
		}

		void Font_Manager::clean()
		{
			m_Fonts.clear();
		}

	}

}