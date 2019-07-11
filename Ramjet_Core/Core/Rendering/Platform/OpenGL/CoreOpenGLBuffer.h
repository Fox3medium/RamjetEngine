#pragma once

#include <Utils/types.h>
#include <Rendering/Renderer/Buffers/BufferLayout.h>

namespace Core 
{
	namespace Rendering 
	{
		namespace API 
		{
			struct Buffer
			{
				uint id;
				uint target, usage;
				uint size;
				BufferLayout layout;

				Buffer(uint target, uint usage);
				~Buffer();

				void resize(uint size);
				void setData(uint size, const void* data);

				template<typename T>
				T* getPointer(uint flags = GL_WRITE_ONLY)
				{
					return (T*)API::getBufferPointer(target, flags);
				}

				void releasePointer();

				void bind();
				void unbind();
			};
		}
	}
}