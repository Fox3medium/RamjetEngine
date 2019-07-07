#pragma once

#include <map>
#include "../Rendering/Renderer/Font/Font.h"

using namespace Core::Rendering;

namespace Core {

	namespace Manager {
	
		class Font_Manager
		{
		private:
			static std::map<std::string, Font*> m_Fonts;

		public:
			static void init();
			static void add(Font* font);
			static Font* get(const std::string& name);
			static Font* get(const std::string& name, unsigned int size);
			static void clean();

		private:
			Font_Manager() {}
			
		};

	}

}

