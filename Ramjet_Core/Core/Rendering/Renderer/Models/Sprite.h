#pragma once

#include "../Renderable2D.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

		class Sprite : public Renderable2D
		{			
		public:

			Maths::vec3& position;
			
		public:			
			Sprite(float x, float y, float width, float height, const unsigned int color);
			Sprite(float x, float y, float width, float height, Texture* texture);

			void setPosition(float x, float y, float z);
			void setPosition(const Maths::vec3& vect);
		};

	}

}

