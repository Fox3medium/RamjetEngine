#include <Utils/types.h>

#include "OpenGL/CoreOpenGLBuffer.h"
#include "OpenGL/CoreOpenGLRender.inl"

namespace Core 
{
	namespace Rendering 
	{
		namespace API
		{
			inline uint createVertexArray();
			inline uint createBuffer();
			inline uint createFramebuffer();
			inline uint createRenderbuffer();

			inline void createVertexArrays(uint size, uint* arrays);
			inline void createVertexBuffers(uint size, uint* buffers);
			inline void createFramebuffers(uint size, uint* buffers);
			inline void createRenderbuffers(uint size, uint* buffers);

			inline void bindVertexArray(uint array);
			inline void bindBuffer(uint target, uint buffer);
			inline void bindFramebuffer(uint target, uint buffer);
			inline void bindRenderbuffer(uint target, uint buffer);

			inline void setBufferData(uint target, uint size, const void* data, uint usage);
			inline void setBufferSubData(uint target, ptrdiff_t offset, ptrdiff_t size, const void* data);
			inline void* getBufferPointer(uint target, uint access);
			inline void releaseBufferPointer(uint target);

			inline void framebufferTexture2D(uint target, uint attachment, uint textarget, uint texture, int level);
			inline void framebufferRenderbuffer(uint target, uint attachment, uint renderbuffertarget, uint renderbuffer);
			inline void renderbufferStorage(uint target, uint format, uint width, uint height);
			inline int getScreenBuffer();

			inline void setViewport(uint x, uint y, uint width, uint height);
			inline void clear(uint flags);
			inline void setClearColor(float r, float g, float b, float a);

			inline uint createTexture();
			inline void createTextures(uint size, uint* textures);
			inline void bindTexture(uint target, uint texture);
			inline void unbindTexture(uint target);
			inline void setTextureParameter(uint target, uint parameter, int value);
			inline void setTextureData(uint target, uint internalformat, uint width, uint height, uint format, uint type, const void* pixels);
			inline void setActiveTexture(uint texture);

			inline void unbindVertexArrays();
			inline void unbindBuffers(uint target);

			inline void enableVertexAttribute(uint index);
			inline void disableVertexAttribute(uint index);
			inline void setVertexAttributePointer(uint index, int size, uint type, bool normalized, uint stride, uint offset);

			inline void freeVertexArray(uint array);
			inline void freeBuffer(uint buffer);
			inline void freeFramebuffer(uint buffer);

			inline void freeVertexArrays(uint size, uint* arrays);
			inline void freeBuffers(uint size, uint* buffers);
			inline void freeFramebuffers(uint framebuffers, uint depthbuffer);

			inline void freeTexture(uint texture);
			inline void freeTextures(uint size, uint* textures);

			inline void drawElements(uint mode, uint count, uint type, const void* indices);
		}
	}
}