#pragma once

#include "../Buffers/FrameBuffer.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/IndexBuffer.h"
#include "PostFXPass.h"

namespace Core {
	
	namespace Rendering {
		
		class PostFX 
		{
		private:
			std::vector<PostFXPass*> m_Passes;

		public:
			PostFX();
			~PostFX();

			void push(PostFXPass* pass);
			void pop();

			void RenderPostFX(FrameBuffer* source, FrameBuffer* target, VertexArray* quad, IndexBuffer* indices);

		};

	}

}