#pragma once

#include <Windows.h>

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <map>

#define CORE_LOG_LEVEL_FATAL	0
#define CORE_LOG_LEVEL_ERROR	1
#define CORE_LOG_LEVEL_WARN		2
#define CORE_LOG_LEVEL_INFO		3

namespace std {

	template <typename T>
	string to_string(const T& t) 
	{
		return std::string("[Unsupported type] " + typeid(T).name() + std::string("!"));
	}

}

namespace Logs 
{

	namespace Internal 
	{
		static char to_string_buffer[1024 * 10];

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};


		template <typename T>
		static const char* to_string_internal(const T& v, const std::true_type& ignored)
		{
			sprintf(to_string_buffer, "Container of size: %d, contents: %s", v.size(), format_iterators(v.begin(), v.end()).c_str());
			return to_string_buffer;
		}

		template <typename T>
		static const char* to_string_internal(const T& t, const std::false_type& ignored)
		{
			auto x = std::to_string(t);
			return strcpy(to_string_buffer, x.c_str());
		}

		template <typename T>
		static const char* to_string(const T& t)
		{
			return to_string_internal<T>(t, std::integral_constant<bool, has_iterator<T>::value>());
		}

		template <>
		static const char* to_string<char>(char const& t)
		{
			return &t;
		}

		template <>
		static const char* to_string<char*>(char* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<char const*>(char const* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<std::string>(std::string const& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}

		template <typename T>
		static std::string format_iterators(T& begin, T& end)
		{
			std::string result;
			bool first = true;
			while (begin != end)
			{
				if (!first)
					result += ", ";
				result += to_string(*begin);
				first = false;
				begin++;
			}
			return result;
		}


		template<typename X, typename Y>
		static const char* to_string(const std::pair<typename X, typename Y>& v)
		{
			sprintf(to_string_buffer, "(Key: %s, Value: %s)", to_string(v.first), to_string(v.second));
			return to_string_buffer;
		}

		template<>
		static const char* to_string_internal<const char*>(const char* const& v, const std::false_type& ignored)
		{
			return v;
		}

		template <typename First>
		static void print_log_internal(char* buffer, int& position, First&& first)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&& ... args)
		{
			const char* formatted = to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
			{
				print_log_internal(buffer, position, std::forward<Args>(args)...);
			}
		}

		template <typename... Args>
		static void log_message(int level, bool newline, Args... args)
		{
			char buffer[1024 * 10];
			int position = 0;
			print_log_internal(buffer, position, std::forward<Args>(args)...);

			if (newline)
				buffer[position++] = '\n';

			buffer[position] = 0;

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			switch (level)
			{
			case CORE_LOG_LEVEL_FATAL:
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			case CORE_LOG_LEVEL_ERROR:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				break;
			case CORE_LOG_LEVEL_WARN:
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				break;
			}
			std::cout << buffer;
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
		}

	}

}

#ifndef CORE_LOG_LEVEL
	#define CORE_LOG_LEVEL CORE_LOG_LEVEL_INFO
#endif // CORE_LOG_LEVEL

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_FATAL
#define CORE_FATAL(...) Logs::Internal::log_message(CORE_LOG_LEVEL_FATAL, true, "/!\\FATAL ERROR /!\\:    ", __VA_ARGS__)
#define _CORE_FATAL(...) Logs::Internal::log_message(CORE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define CORE_FATAL(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_ERROR
#define CORE_ERROR(...) Logs::Internal::log_message(CORE_LOG_LEVEL_ERROR, true, "ERROR:    ", __VA_ARGS__)
#else
#define CORE_ERROR(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_WARN
#define CORE_WARN(...) Logs::Internal::log_message(CORE_LOG_LEVEL_WARN, true, "WARNING:    ", __VA_ARGS__)
#else
#define CORE_WARN(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_INFO
#define CORE_INFO(...) Logs::Internal::log_message(CORE_LOG_LEVEL_INFO, true, "INFO:    ", __VA_ARGS__)
#else
#define CORE_INFO(...)
#endif 

#define CORE_ASSERT(x, ...) \
	do { \
	if (!(x)) \
		{ \
		char* file = __FILE__; \
		unsigned int last = 0; \
		char* c; \
		for (c = file; *c != '\0'; c++) \
				{ \
			if (*c == '\\' || *c == '/') \
				last = c - file; \
				} \
		CORE_FATAL(""); \
		CORE_FATAL("*************************"); \
		CORE_FATAL("    ASSERTION FAILED!    "); \
		CORE_FATAL("*************************"); \
		CORE_FATAL(#x); \
		CORE_FATAL(__VA_ARGS__); \
		_CORE_FATAL("-> "); \
		for (int i = last + 1; i < c - file; i++) \
			_CORE_FATAL(file[i]); \
		_CORE_FATAL(":", __LINE__, "\n"); \
		*(int*)NULL = 8; \
		} \
	} while(0)