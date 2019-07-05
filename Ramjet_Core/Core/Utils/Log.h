#pragma once

#include <stdio.h>

#define CORE_ASSERT(x, m) do { if (!(x)) { \char* file = __FILE__; \
		unsigned int last = 0; \
		char* c; \
		for (c = file; *c != '\0'; c++) \
				{ \
				CORE_LOG_LEVEL \
			if (*c == '\\' || *c == '/') \
				last = c - file; \
				} \
		printf("\n"); \
		printf("*************************\n"); \
		printf("    ASSERTION FAILED!    \n"); \
		printf("*************************\n"); \
		printf("%s\n", #x); \
		char* message = m; \
		if (message[0] != '\0') \
			printf("%s\n", m); \
		printf("-> "); \
		for (int i = last + 1; i < c - file; i++) \
			printf("%c", file[i]); \
		printf(":%d\n", __LINE__); \
		*(int*)NULL = 8; \
	} \
	} while(0) 

#define CORE_LOG_ERROR_FATAL	0
#define CORE_LOG_ERROR_ERROR	1
#define CORE_LOG_ERROR_WARN		2
#define CORE_LOG_ERROR_INFO		3

#ifndef CORE_LOG_LEVEL
	#define CORE_LOG_LEVEL CORE_LOG_ERROR_INFO
#endif // CORE_LOG_LEVEL

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_FATAL
#define CORE_FATAL(x, ...) do { printf("[CORE][FATAL]: "); printf(x, __VA_ARGS__); printf("\n"); CORE_ASSERT(false, ""); } while(0)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_ERROR
#define CORE_ERROR(x, ...) do { printf("[CORE][ERROR]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_WARN
#define CORE_WARN(x, ...) do { printf("[CORE][WARN]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif

#if CORE_LOG_LEVEL >= CORE_LOG_LEVEL_INFO
#define CORE_INFO(x, ...) do { printf("[CORE][INFO]: "); printf(x, __VA_ARGS__); printf("\n"); } while(0)
#endif 

