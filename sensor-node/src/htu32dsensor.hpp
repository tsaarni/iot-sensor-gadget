
#pragma once

#include <Adafruit_HTU21DF.h>


class Htu32dSensor
{
public:
   Htu32dSensor();
   void publish();
   
private:
   Adafruit_HTU21DF htu_;
};

