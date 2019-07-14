#include "Layer2D.h"
#include <CoreBasicInclude.h>
#include "../Batch2DRenderer.h"

namespace Core {

	namespace Rendering {

		Layer2D::Layer2D(Shader* shader, Maths::mat4 projectionMatrix)
			: m_Renderer(new Batch2DRenderer(m_Window->getWidth(), m_Window->getHeight())) 
			, m_Shader(shader), m_ProjectionMatrix(projectionMatrix)
		{			
			m_Shader->enable();
			m_Shader->setUniformMat4("pr_matrix", m_ProjectionMatrix);			
			
			int texIDs[] =
			{
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_Shader->setUniform1iv("textures", texIDs, 32);

			m_Shader->disable();		

		}

		Layer2D::~Layer2D()
		{
			delete m_Shader;
			delete m_Renderer;
			for (uint i = 0; i < m_Renderables.size(); i++)
				delete m_Renderables[i];
		}

		void Layer2D::init()
		{
			onInit(*m_Renderer, *m_Shader);
		}

		void Layer2D::onInit(Renderer2D& renderer, Shader& shader)
		{
		}

		void Layer2D::add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Layer2D::onRender()
		{
			m_Shader->enable();
			m_Renderer->begin();

			for (const Renderable2D* renderable : m_Renderables)
				renderable->submit(m_Renderer);

			m_Renderer->end();
			m_Renderer->flush();

			onRender(*m_Renderer);
		}

		void Layer2D::onRender(Renderer2D& renderer)
		{

			m_Shader->enable();
			m_Renderer->begin();

			for (const Renderable2D* renderable : m_Renderables)
				renderable->submit(m_Renderer);

			for (const Renderable2D* renderable : m_SubmittedRenderables)
				renderable->submit(m_Renderer);

			m_Renderer->end();
			m_Renderer->flush();

			onRender(*m_Renderer);

			m_SubmittedRenderables.clear();
		}

		Renderable2D* Layer2D::submit(Renderable2D* renderable)
		{
			m_SubmittedRenderables.push_back(renderable);
			return renderable;
		}

	}

}