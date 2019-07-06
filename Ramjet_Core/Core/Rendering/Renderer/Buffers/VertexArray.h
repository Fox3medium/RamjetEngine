#pragma once

#include <vector>
#include <GLEW/glew.h>

#include "Buffer.h"

namespace Core {

	namespace Rendering {

		class VertexArray
		{
		private:
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;

		public:
			VertexArray();
			~VertexArray();

			/*
			@buffer : the buffer you want to add
			@index : index of this buffer into the vertexShader (location index)
			*/
			void addBuffer(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};

	}
}

