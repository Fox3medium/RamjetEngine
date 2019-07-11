#include "Layer3D.h"

#include "../ForwardRenderer.h"

namespace Core
{
	namespace Rendering
	{

		Layer3D::Layer3D(Scene* scene)
			: m_Scene(scene), m_Renderer(new ForwardRenderer())
		{
		}

		Layer3D::~Layer3D()
		{
			delete m_Scene;
			delete m_Renderer;
		}

		void Layer3D::init()
		{
			onInit(*m_Renderer, *m_Scene);
		}

		void Layer3D::onInit(Renderer3D& renderer, Scene& scene)
		{
		}

		void Layer3D::onRender()
		{
			onRender(*m_Renderer);
		}

		void Layer3D::onRender(Renderer3D& renderer)
		{
			m_Scene->render(renderer);
			renderer.flush();
		}

	}

}
