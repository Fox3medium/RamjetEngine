#pragma once

#include <Utils/Maths/maths.h>
#include <vector>
#include "Font/Font.h"
#include <Managers/Font_Manager.h>
#include "Texture/Texture.h"
#include "Texture/Mask.h"
#include "PostFX/PostFX.h"

namespace Core {

	namespace Rendering {
										
		#define DEBUG_COLOR_RED			0xFF0000FF
		#define DEBUG_COLOR_GREEN		0x00FF00FF
		#define DEBUG_COLOR_BLUE		0x0000FFFF
		#define DEBUG_COLOR_WHITE		0xFFFFFFFF
		#define DEBUG_COLOR_BLACK		0x000000FF
		#define DEBUG_BACKGROUND		0x505050DD

		class Renderable2D;
	
		enum class CORE_API RenderTarget
		{
			SCREEN = 0,
			BUFFER = 1
		};

		class CORE_API Renderer2D
		{
		protected:

			std::vector<Maths::mat4> m_TransformationStack;
			const Maths::mat4* m_TransformationBack;
			const Mask* m_Mask;
			RenderTarget m_Target;
			PostFX* m_PostFX;
			bool m_PostFXEnabled;

		protected:
			Renderer2D() 
				: m_Mask(nullptr), m_PostFXEnabled(false)
			{
				m_TransformationStack.push_back(Maths::mat4::Identity());
				m_TransformationBack = &m_TransformationStack.back();
				m_Target = RenderTarget::SCREEN;
			}		

		public:
			virtual ~Renderer2D() {}

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const String& text, const Maths::vec2& position, const Font& font = *Manager::Font_Manager::get(), uint Color = 0xffffffff) {};
			virtual void drawLine(float x0, float y0, float x1, float y1, float thickness = 0.02f, uint color = 0xffffffff) { }
			virtual void drawLine(const Maths::vec2& start, const Maths::vec2& end, float thickness = 0.02f, uint color = 0xffffffff) { }
			virtual void drawRect(float x, float y, float width, float height, uint color = 0xffffffff) { }
			virtual void drawRect(const Maths::Rectangle& rectangle, uint color = 0xffffffff) { }

			virtual void fillRect(float x, float y, float width, float height, uint color = 0xffffffff) {};
			virtual void fillRect(const Maths::Rectangle& rectangle, uint color = 0xffffffff) { }
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

			virtual void setMask(const Mask* mask) { m_Mask = mask; }

			inline void setRenderTarget(RenderTarget target) { m_Target = target; }
			inline const RenderTarget getRenderTarget() const { return m_Target; }

			inline void  setPostFX(bool enabled) { m_PostFXEnabled = enabled; }
			inline bool getPostFX() const { return m_PostFXEnabled; }
			inline void addPostFXPass(PostFXPass* pass) { m_PostFX->push(pass); }

		};

	}

}


