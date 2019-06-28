#pragma once

#include <GLEW\glew.h>

namespace Core {

	namespace Rendering {
	
		class IndexBuffer
		{
		private:
			GLuint m_BufferID;
			GLuint m_Count;

		public:
			IndexBuffer(GLuint* data, GLsizei count);

			void bind() const;
			void unbind() const;

			// Return the number of index 
			inline GLuint getCount() const { return m_Count; }
		};

	}

}



