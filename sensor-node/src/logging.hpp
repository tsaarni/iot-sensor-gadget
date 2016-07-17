
#pragma once

#include <stdio.h>
#include <Arduino.h>


#define LOG_INFO(msg) logging_println_(LOGGING_PREFIX_INFO_, msg)
#define LOG_ERROR(msg) logging_println_(LOGGING_PREFIX_ERROR_, msg)



#define LOGGING_STR_(x) LOGGING_STR2_(x)
#define LOGGING_STR2_(x) #x
#define LOGGING_LINE_ LOGGING_STR_(__LINE__)
#define LOGGING_PREFIX_ERROR_ __FILE__ ":" LOGGING_LINE_ " ERROR: "
#define LOGGING_PREFIX_INFO_ __FILE__ ":" LOGGING_LINE_ " INFO: "


inline void
logging_println_(const char* filelinelevel, const char* msg)
{
   static char buf[128];
   snprintf(buf, sizeof(buf), "%s%s", filelinelevel, msg);
   Serial.println(buf);
}
