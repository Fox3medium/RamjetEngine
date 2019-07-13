#include "Group.h"
#include <CoreBasicInclude.h>

namespace Core {

	namespace Rendering {

		Group::Group(const Maths::mat4& transform)
			: m_TransformationMatrix(transform)
		{
		}

		Group::~Group()
		{
			for (int i = 0; i < m_Children.size(); i++)
				delete m_Children[i];
		}

		void Group::add(Renderable2D* renderable)
		{
			m_Children.push_back(renderable);
		}

		void Group::submit(Renderer2D* renderer) const
		{
			renderer->push(m_TransformationMatrix);

			for (const Renderable2D* renderable : m_Children)
				renderable->submit(renderer);

			renderer->pop();
		}

	}
}