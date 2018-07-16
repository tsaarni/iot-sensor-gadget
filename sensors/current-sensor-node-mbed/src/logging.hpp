
#pragma once

#define LOG_INFO(...) logging_println_(LOGGING_PREFIX_INFO_, __VA_ARGS__)
#define LOG_ERROR(...) logging_println_(LOGGING_PREFIX_ERROR_, __VA_ARGS__)

#define LOGGING_STR_(x) LOGGING_STR2_(x)
#define LOGGING_STR2_(x) #x
#define LOGGING_LINE_ LOGGING_STR_(__LINE__)
#define LOGGING_PREFIX_ERROR_ __FILE__ ":" LOGGING_LINE_ " ERROR: "
#define LOGGING_PREFIX_INFO_ __FILE__ ":" LOGGING_LINE_ " INFO: "

extern void logging_println_(const char* filelinelevel, const char* fmt, ...);
