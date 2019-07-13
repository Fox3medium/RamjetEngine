#pragma once

#include <CoreBasicInclude.h>
#include <Core/Common.h>
#include <Utils/types.h>
#include <Utils/Maths/vec2.h>

#define CORE_LOG_LEVEL_FATAL	0
#define CORE_LOG_LEVEL_ERROR	1
#define CORE_LOG_LEVEL_WARN		2
#define CORE_LOG_LEVEL_INFO		3

namespace std {

	template <typename T>
	string to_string(const T& t)
	{
		return string("[Unsupported type] " + typeid(T).name() + String("!"));
	}

}

namespace Logs
{

	namespace Internal
	{
		static char to_string_buffer[1024 * 10];

		CORE_API void PlatformLogMessage(uint level, const char* message);

		template <class T>
		struct has_iterator
		{
			template<class U> static char(&test(typename U::iterator const*))[1];
			template<class U> static char(&test(...))[2];
			static const bool value = (sizeof(test<T>(0)) == 1);
		};

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
		static const char* to_string<unsigned char const*>(unsigned char const* const& t)
		{
			return (const char*)t;
		}


		template <>
		static const char* to_string<char const*>(char const* const& t)
		{
			return t;
		}

		template <>
		static const char* to_string<String>(const String& t)
		{
			return t.c_str();
		}

		template <>
		static const char* to_string<Maths::vec2>(const Maths::vec2& t)
		{
			// TODO: sprintf
			String string = String("vec2: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <>
		static const char* to_string<Maths::vec3>(const Maths::vec3& t)
		{
			// TODO: sprintf
			String string = String("vec3: (") + std::to_string(t.x) + ", " + std::to_string(t.y) + ", " + std::to_string(t.z) + ")";
			char* result = new char[string.length()];
			strcpy(result, &string[0]);
			return result;
		}

		template <typename T>
		static String format_iterators(T& begin, T& end)
		{
			String result;
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
			const char* formatted = Logs::Internal::to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
		}

		template <typename First, typename... Args>
		static void print_log_internal(char* buffer, int& position, First&& first, Args&& ... args)
		{
			const char* formatted = Logs::Internal::to_string<First>(first);
			int length = strlen(formatted);
			memcpy(&buffer[position], formatted, length);
			position += length;
			if (sizeof...(Args))
				print_log_internal(buffer, position, std::forward<Args>(args)...);
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

			PlatformLogMessage(level, buffer);
		}

	}

}

// Windows (wingdi.h) defines CORE_ERROR
#ifdef CORE_ERROR
#undef CORE_ERROR
#endif

#ifndef CORE_LOG_LEVEL
#define CORE_LOG_LEVEL CORE_LOG_LEVEL_INFO
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_FATAL
#define CORE_FATAL(...) Logs::Internal::log_message(CORE_LOG_LEVEL_FATAL, true, "/!\\ FATAL /!\\:    ", __VA_ARGS__)
#define _CORE_FATAL(...) Logs::Internal::log_message(CORE_LOG_LEVEL_FATAL, false, __VA_ARGS__)
#else
#define CORE_FATAL(...)
#define _CORE_FATAL(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_ERROR
#define CORE_ERROR(...) Logs::Internal::log_message(CORE_LOG_LEVEL_ERROR, true, "ERROR:    ", __VA_ARGS__)
#define _CORE_ERROR(...) Logs::Internal::log_message(CORE_LOG_LEVEL_ERROR, false, __VA_ARGS__)
#else
#define CORE_ERROR(...)
#define _CORE_ERROR(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_WARN
#define CORE_WARN(...) Logs::Internal::log_message(CORE_LOG_LEVEL_WARN, true, "WARNING:    ", __VA_ARGS__)
#define _CORE_WARN(...) Logs::Internal::log_message(CORE_LOG_LEVEL_WARN, false, __VA_ARGS__)
#else
#define CORE_WARN(...)
#define _CORE_WARN(...)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_INFO
#define CORE_INFO(...) Logs::Internal::log_message(CORE_LOG_LEVEL_INFO, true, "INFO:    ", __VA_ARGS__)
#define _CORE_INFO(...) Logs::Internal::log_message(CORE_LOG_LEVEL_INFO, false, __VA_ARGS__)
#else
#define CORE_INFO(...)
#define _CORE_INFO(...)
#endif

#ifdef CORE_DEBUG
#define CORE_ASSERT(x, ...) \
		if (!(x)) {\
			CORE_FATAL("*************************"); \
			CORE_FATAL("    ASSERTION FAILED!    "); \
			CORE_FATAL("*************************"); \
			CORE_FATAL(__FILE__, ": ", __LINE__); \
			CORE_FATAL("Condition: ", #x); \
			CORE_FATAL(__VA_ARGS__); \
			__debugbreak(); \
		}
#else
#define CORE_ASSERT(x, ...)
#endif

void check_error();
bool log_gl_call(const char* function, const char* file, int line);

#ifdef CORE_DEBUG
#define GLCall(x) check_error();\
		x; \
		if (!log_gl_call(#x, __FILE__, __LINE__)) __debugbreak();
#else
#define GLCall(x) x
#endif
