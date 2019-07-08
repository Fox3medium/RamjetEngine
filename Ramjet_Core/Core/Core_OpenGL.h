#pragma once

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <Utils/Log.h>

static void log_gl_call(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		CORE_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
	}
}

#ifdef CORE_DEBUG
#define GLCall(x) glGetError();\
		x; \
		log_gl_call(#x, __FILE__, __LINE__);
#else
#define GLCall(x) x
#endif