#pragma once

#include "../Buffers/FrameBuffer.h"
#include "../Shader/Shader.h"
#include <Core/Common.h>

namespace Core {

	namespace Rendering {
	
		class CORE_API PostFXPass 
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