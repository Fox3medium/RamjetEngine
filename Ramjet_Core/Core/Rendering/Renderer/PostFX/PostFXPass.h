#pragma once

#include "../Buffers/FrameBuffer.h"
#include "../Shader/Shader.h"

namespace Core {

	namespace Rendering {
	
		class PostFXPass 
		{
		private:
			Shader* m_Shader;

		public:
			PostFXPass(Shader* shader);
			~PostFXPass();

			void RenderPass(FrameBuffer* target);
		};

	}
}