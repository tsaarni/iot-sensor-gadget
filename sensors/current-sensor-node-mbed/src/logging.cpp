
#include "mbed.h"

#include "logging.hpp"

Serial pc(PA_9,    // tx
          PA_10,   // rx
          115200); // baud rate

void
logging_println_(const char* filelinelevel, const char* fmt, ...)
{
   pc.puts(filelinelevel);

   va_list args;
   va_start(args, fmt );
   pc.vprintf(fmt, args);
   va_end (args);

   pc.putc('\n');
}
