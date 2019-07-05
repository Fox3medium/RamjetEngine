#pragma once

#include "../Renderable2D.h"
#include "../Renderer2D.h"

namespace Core {

	namespace Rendering {
		
		class Layer
		{
		protected:
			Renderer2D* m_Renderer;
			std::vector<Renderable2D*> m_Renderables;
			Shader* m_Shader;
			Maths::mat4 m_ProjectionMatrix;			

		public:
			Layer(Renderer2D* renderer, Shader* shader, Maths::mat4 projectionMatrix);
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

			inline const std::vector<Renderable2D*>& getRenderable() const { return m_Renderables; }

		};

	}

}

