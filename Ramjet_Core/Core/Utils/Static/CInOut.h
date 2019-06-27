#pragma once

#include <string>
#include <Utils\Maths\maths.h>
#include <Utils\String.h>

namespace Utils {

	class CInOut {

	public:

		static void Out(int s);
		static void Out(double s);
		static void Out(String s);
		static void Out(bool b);
		static void Out(const char* c);
		static void Out(const unsigned char* c);
		static void Out(String s, const unsigned char* c);
		/*static void Out(String s, GLenum en);*/
		/*static void Out(String s, const GLchar* gchar);*/
		/*static void Out(GLenum en);*/
		/*static void Out(GLchar* gchar);*/
		static void Out(std::string s);
		static void Out(vec2 vec);
		static void Out(vec3 vec);
		static void Out(vec4 vec);
		static void Out(mat4 mat);


		static String In();

	};
}
