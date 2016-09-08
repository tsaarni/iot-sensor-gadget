
#include <Arduino.h>

#include "Gateway.hpp"


Gateway gw(/*cs pin*/D1, /*ce pin*/D2);

void
setup()
{
   gw.init();
}

void
loop()
{
   gw.loop();
}
