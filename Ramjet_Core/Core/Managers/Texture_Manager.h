#pragma once

#include <map>
#include <Utils/types.h>
#include "../Rendering/Renderer/Texture/Texture.h"

namespace Core {

	using namespace Rendering;

	namespace Manager {
	
		class Texture_Manager
		{
		private:
			static std::map < String, Texture* > m_Textures;

		public:
			static void add(Texture* texture);
			static Texture* get(const String& name);
			static void clean();

		private:
			Texture_Manager() {}
		};

	}

}

