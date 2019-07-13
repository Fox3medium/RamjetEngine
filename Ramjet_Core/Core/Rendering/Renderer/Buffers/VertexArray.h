#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include "Buffer.h"
#include <Utils/types.h>

namespace Core {

	namespace Rendering {		

		class CORE_API VertexArray
		{
		private:
			uint m_ArrayID;
			std::vector<API::Buffer*> m_Buffers;
			static uint s_CurrentBinding;

		public:
			VertexArray();
			~VertexArray();

			API::Buffer* getBuffer(uint index = 0);

			/*
			@buffer : the buffer you want to add
			@index : index of this buffer into the vertexShader (location index)
			*/
			void addBuffer(API::Buffer* buffer);
			void bind() const;
			void unbind() const;

			void draw(uint count) const;
		};

	}
}

