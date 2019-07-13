#include <CoreBasicInclude.h>
#include "CoreOpenGLBuffer.h"

#include <Rendering/Platform/CoreRenderAPI.h>

namespace Core
{
	namespace Rendering
	{
		namespace API
		{
			Buffer::Buffer(uint target, uint usage)
				: target(target), usage(usage)
			{
				id = createBuffer();
			}

			Buffer::~Buffer()
			{
				freeBuffer(id);
			}

			void Buffer::resize(uint size)
			{
				this->size = size;
				setBufferData(target, size, NULL, usage);
			}

			void Buffer::setData(uint size, const void* data)
			{
				setBufferData(target, size, data, usage);
			}

			void Buffer::releasePointer()
			{
				API::releaseBufferPointer(target);
			}

			void Buffer::bind()
			{
				bindBuffer(target, id);
			}

			void Buffer::unbind()
			{
				unbindBuffers(target);
			}
		}
	}
}