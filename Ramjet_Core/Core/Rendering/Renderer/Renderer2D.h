#pragma once

#include <GLEW/glew.h>
#include <Utils/Maths/maths.h>
#include <vector>
#include "Font/Font.h"

using namespace Utils;

namespace Core {

	namespace Rendering {

		#define CONSOLE_COLOR_RED		0xFF0000FF
		#define CONSOLE_COLOR_GREEN		0x00FF00FF
		#define CONSOLE_COLOR_BLUE		0x0000FFFF
		#define CONSOLE_COLOR_WHITE		0xFFFFFFFF
		#define CONSOLE_COLOR_BLACK		0x000000FF
		#define CONSOLE_BACKGROUND		0x505050DD

		class Renderable2D;
	
		class Renderer2D
		{
		protected:

			std::vector<Maths::mat4> m_TransformationStack;
			const Maths::mat4* m_TransformationBack;

		public:
			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const Maths::vec3& position, const Font& font, unsigned int Color) {};
			virtual void flush() = 0;
			virtual void end() {}

			void push(const Maths::mat4& matrix, bool override = false) {
				if (override)
					m_TransformationStack.push_back(matrix);
				else
					m_TransformationStack.push_back(m_TransformationStack.back() * matrix);

				m_TransformationBack = &m_TransformationStack.back();
			}

			void pop() {
				if (m_TransformationStack.size() > 1)
					m_TransformationStack.pop_back();

				m_TransformationBack = &m_TransformationStack.back();
			}
		
			virtual ~Renderer2D() {}
		protected:
			Renderer2D() {
				m_TransformationStack.push_back(Maths::mat4::identity());
				m_TransformationBack = &m_TransformationStack.back();
			}		

		};

	}

}


