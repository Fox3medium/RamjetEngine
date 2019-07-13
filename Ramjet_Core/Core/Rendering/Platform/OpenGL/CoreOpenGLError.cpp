#include <CoreBasicInclude.h>
#include <Utils/Log.h>
#include <GLEW/glew.h>

void check_error() 
{
	glGetError();
}

bool log_gl_call(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if(error != GL_NO_ERROR) 
	{
		CORE_ERROR("[OpenGL error] (", error, "): ", function, " ", file, " : ", line);
		return false;
	}
	return true;
}