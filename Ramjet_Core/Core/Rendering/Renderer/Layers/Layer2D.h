#pragma once

#include "Layer.h"

#include <Core/Common.h>

#include "../Renderable2D.h"
#include "../Texture/Mask.h"
#include <Utils/types.h>

namespace Core {

	namespace Rendering {
		
		class CORE_API Layer2D : public Layer
		{
		public:
			Renderer2D* m_Renderer;

		protected:
			std::vector<Renderable2D*> m_Renderables;
			std::vector<Renderable2D*> m_SubmittedRenderables;
			Shader* m_Shader;
			Maths::mat4 m_ProjectionMatrix;			

		public:
			Layer2D(Shader* shader, Maths::mat4 projectionMatrix);
			virtual ~Layer2D();

			virtual void init();
			virtual void onInit(Renderer2D& renderer, Shader& shader);

			virtual void add(Renderable2D* renderable);
			void onRender();
			virtual void onRender(Renderer2D& renderer);

			virtual Renderable2D* submit(Renderable2D* renderable);

			inline void setMask(const Mask* mask) const { m_Renderer->setMask(mask); }

			inline const std::vector<Renderable2D*>& getRenderable() const { return m_Renderables; }

		};

	}

}

