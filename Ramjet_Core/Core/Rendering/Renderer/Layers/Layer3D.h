#pragma once

#include "Layer.h"
#include <Rendering/Scene/Scene.h>

namespace Core 
{
	namespace Rendering 
	{
		class Layer3D : public Layer 
		{
		protected:
			Scene* m_Scene;
			Renderer3D* m_Renderer;

		public:
			Layer3D(Scene* scene);
			~Layer3D();

			virtual void init();
			virtual void onInit(Renderer3D& renderer, Scene& scene);

			inline Scene* getScene() const { return m_Scene; }

			void onRender() override;
			virtual void onRender(Renderer3D& renderer);
		};
	}
}