#pragma once

#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core {

	namespace Rendering {
	
		class IndexBuffer
		{
		private:
			uint m_Count;
			API::Buffer* m_Buffer;

		public:
			IndexBuffer(short* data, uint count);
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			// Return the number of index 
			inline uint getCount() const { return m_Count; }
		};

	}

}



