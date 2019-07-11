#pragma once

#include "Layer.h"

#include "../Renderable2D.h"
#include "../Renderer2D.h"
#include <Utils/types.h>

namespace Core {

	namespace Rendering {
		
		class Layer2D : public Layer
		{
		public:
			Renderer2D* m_Renderer;

		protected:
			std::vector<Renderable2D*> m_Renderables;
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


			inline void setMask(const Mask* mask) const { m_Renderer->setMask(mask); }

			inline const std::vector<Renderable2D*>& getRenderable() const { return m_Renderables; }

		};

	}

}

