#pragma once

#include <Utils/Log.h>
#include <GLEW/glew.h>

namespace Core 
{
	namespace Rendering 
	{
		namespace API 
		{
			inline uint createVertexArray()
			{
				uint result;
				glGenVertexArrays(1, &result);
				return result;
			}

			inline uint createBuffer()
			{
				uint result;
				glGenBuffers(1, &result);
				return result;
			}

			inline uint createFramebuffer()
			{
				uint result;
				glGenFramebuffers(1, &result);
				return result;
			}

			inline uint createRenderbuffer()
			{
				uint result;
				glGenRenderbuffers(1, &result);
				return result;
			}

			inline void createVertexArrays(uint size, uint* arrays)
			{
				glGenVertexArrays(size, arrays);
			}

			inline void createVertexBuffers(uint size, uint* buffers)
			{
				glGenVertexArrays(size, buffers);
			}

			inline void createFramebuffers(uint size, uint* buffers)
			{
				glGenFramebuffers(size, buffers);
			}

			inline void createRenderbuffers(uint size, uint* buffers)
			{
				glGenRenderbuffers(size, buffers);
			}

			inline void bindVertexArray(uint array)
			{
				glBindVertexArray(array);
			}

			inline void bindBuffer(uint target, uint buffer)
			{
				glBindBuffer(target, buffer);
			}

			inline void bindFramebuffer(uint target, uint buffer)
			{
				glBindFramebuffer(target, buffer);
			}

			inline void bindRenderbuffer(uint target, uint buffer)
			{
				glBindRenderbuffer(target, buffer);
			}

			inline int getScreenBuffer()
			{
				int result;
				glGetIntegerv(GL_FRAMEBUFFER_BINDING, &result);
				return result;
			}

			inline void setBufferData(uint target, uint size, const void* data, uint usage)
			{
				glBufferData(target, size, data, usage);
			}

			inline void setBufferSubData(uint target, ptrdiff_t offset, ptrdiff_t size, const void* data)
			{
				glBufferSubData(target, offset, size, data);
			}

			inline void* getBufferPointer(uint target, uint access)
			{
				void* result = glMapBuffer(target, access);
				return result;
			}

			inline void releaseBufferPointer(uint target)
			{
				glUnmapBuffer(target);
			}

			inline void framebufferTexture2D(uint target, uint attachment, uint textarget, uint texture, int level)
			{
				glFramebufferTexture2D(target, attachment, textarget, texture, level);
			}

			inline void framebufferRenderbuffer(uint target, uint attachment, uint renderbuffertarget, uint renderbuffer)
			{
				glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
			}

			inline void renderbufferStorage(uint target, uint format, uint width, uint height)
			{
				glRenderbufferStorage(target, format, width, height);
			}

			inline void setViewport(uint x, uint y, uint width, uint height)
			{
				glViewport(x, y, width, height);
			}

			inline void clear(uint flags)
			{
				glClear(flags);
			}

			inline void setClearColor(float r, float g, float b, float a)
			{
				glClearColor(r, g, b, a);
			}

			inline uint createTexture()
			{
				GLuint result;
				glGenTextures(1, &result);
				return result;
			}

			inline void createTextures(uint size, uint* textures)
			{
				glGenTextures(size, textures);
			}

			inline void bindTexture(uint target, uint texture)
			{
				glBindTexture(target, texture);
			}

			inline void unbindTexture(uint target)
			{
				glBindTexture(target, 0);
			}

			inline void setTextureParameter(uint target, uint parameter, int value)
			{
				glTexParameteri(target, parameter, value);
			}

			inline void setTextureData(uint target, uint internalformat, uint width, uint height, uint format, uint type, const void* pixels)
			{
				glTexImage2D(target, 0, internalformat, width, height, 0, format, type, pixels);
			}

			inline void setActiveTexture(uint texture)
			{
				glActiveTexture(texture);
			}

			inline void unbindVertexArrays()
			{
				glBindVertexArray(0);
			}

			inline void unbindBuffers(uint target)
			{
				glBindBuffer(target, 0);
			}

			inline void enableVertexAttribute(uint index)
			{
				glEnableVertexAttribArray(index);
			}

			inline void disableVertexAttribute(uint index)
			{
				glDisableVertexAttribArray(index);
			}

			inline void setVertexAttributePointer(uint index, int size, uint type, bool normalized, uint stride, uint offset)
			{
				glVertexAttribPointer(index, size, type, (uint)normalized, stride, (const GLvoid*)offset);
			}

			inline void freeArray(uint array)
			{
				glDeleteVertexArrays(1, &array);
			}

			inline void freeBuffer(uint buffer)
			{
				glDeleteBuffers(1, &buffer);
			}

			inline void freeFramebuffer(uint buffer)
			{
				glDeleteFramebuffers(1, &buffer);
			}

			inline void freeVertexArray(uint array)
			{
				glDeleteVertexArrays(1, &array);
			}

			inline void freeVertexArrays(uint size, uint* arrays)
			{
				glDeleteVertexArrays(size, arrays);
			}

			inline void freeBuffers(uint size, uint* buffers)
			{
				glDeleteBuffers(size, buffers);
			}

			inline void freeFramebuffers(uint framebuffers, uint depthbuffer)
			{
				glDeleteFramebuffers(1, &framebuffers);
				glDeleteRenderbuffers(1, &depthbuffer);
			}

			inline void freeTexture(uint texture)
			{
				glDeleteTextures(1, &texture);
			}

			inline void freeTextures(uint size, uint* textures)
			{
				glDeleteTextures(size, textures);
			}

			inline void drawElements(uint mode, uint count, uint type, const void* indices)
			{
				glDrawElements(mode, count, type, indices);
			}
		}
	}
}