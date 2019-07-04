#pragma once

#include "../Renderable2D.h"

namespace Core {

	namespace Rendering {
	
		class Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Children;
			Maths::mat4 m_TransformationMatrix;

		public:
			Group(const Maths::mat4& transform);
			~Group();
			void add(Renderable2D* renderable);
			void submit(Renderer2D* renderer) const override;
		};

	}

}

