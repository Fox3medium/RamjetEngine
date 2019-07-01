#include "CInOut.h"

namespace Utils {


	void CInOut::Out(int s)
	{
		std::cout << s << std::endl;
	}

	void CInOut::Out(double s)
	{
		std::cout << s << std::endl;
	}

	void CInOut::Out(String s)
	{
		std::cout << s << std::endl;
	}

	void CInOut::Out(bool b)
	{
		std::cout << String::toString(b) << std::endl;
	}

	void CInOut::Out(const char* c)
	{
		std::cout << c << std::endl;
	}

	void CInOut::Out(const unsigned char* c)
	{
		std::cout << c << std::endl;
	}

	void CInOut::Out(String s, const unsigned char* c)
	{
		std::cout << s << c << std::endl;
	}

	//void CInOut::Out(String s, GLenum en)
	//{
	//	std::cout << s << en << std::endl;
	//}

	//void CInOut::Out(String s, const GLchar* gchar)
	//{
	//	std::cout << s << gchar << std::endl;
	//}

	//void CInOut::Out(GLchar* gchar)
	//{
	//	std::cout << gchar << std::endl;
	//}

	void CInOut::Out(std::string s)
	{
		std::cout << s << std::endl;
	}

	void CInOut::Out(Maths::vec2 vec)
	{
		std::cout << "vec2 x : " << vec.x << " y : " << vec.y << std::endl;
	}

	void CInOut::Out(Maths::vec3 vec)
	{
	}

	void CInOut::Out(Maths::vec4 vec)
	{
	}

	void CInOut::Out(Maths::mat4 mat)
	{
	}

	String CInOut::In()
	{
		std::string In;
		std::cin >> In;
		return String(In.c_str());
	}

}
