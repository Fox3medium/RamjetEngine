#pragma once

#include <map>
#include <Utils/types.h>
#include "../Rendering/Renderer/Font/Font.h"

using namespace Core::Rendering;

namespace Core {

	namespace Manager {
	
		class Font_Manager
		{
		private:
			static std::map<String, Font*> m_Fonts;

		public:
			static void init();
			static void add(Font* font);
			static Font* get();
			static Font* get(const String& name);
			static Font* get(const String& name, unsigned int size);
			static void clean();

		private:
			Font_Manager() {}
			
		};

	}

}

