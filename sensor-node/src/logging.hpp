
#pragma once

#include <stdio.h>
#include <Arduino.h>


#define LOG_INFO(...) logging_println_(LOGGING_PREFIX_INFO_, __VA_ARGS__)
#define LOG_ERROR(...) logging_println_(LOGGING_PREFIX_ERROR_, __VA_ARGS__)



#define LOGGING_STR_(x) LOGGING_STR2_(x)
#define LOGGING_STR2_(x) #x
#define LOGGING_LINE_ LOGGING_STR_(__LINE__)
#define LOGGING_PREFIX_ERROR_ __FILE__ ":" LOGGING_LINE_ " ERROR: "
#define LOGGING_PREFIX_INFO_ __FILE__ ":" LOGGING_LINE_ " INFO: "


inline void
logging_println_(const char* filelinelevel, const char* fmt, ...)
{
   static char buf[128];

   strncpy(buf, filelinelevel, sizeof(buf));

   size_t len = strlen(buf);
   va_list args;
   va_start(args, fmt );
   vsnprintf(buf + len, sizeof(buf) - len, fmt, args);
   va_end (args);
   Serial.println(buf);
}
