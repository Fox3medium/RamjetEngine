#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include <Utils/types.h>
#include "../Rendering/Renderer/Font/Font.h"

using namespace Core::Rendering;

namespace Core {

	namespace Manager {
	
		class CORE_API Font_Manager
		{
		private:
			static std::map<String, Font*> m_Fonts;
			static Maths::vec2 s_Scale;

		public:
			static void init();
			static void add(Font* font);
			static Font* get();
			static Font* get(const String& name);
			static Font* get(const String& name, unsigned int size);
			static Font* get(uint size);
			static void clean();

			static void setScale(const Maths::vec2& scale) { s_Scale = scale; }

		private:
			Font_Manager() {}
			
		};

	}

}

