
#include "logging.hpp"
#include "gateway.hpp"
#include "lightsensor.hpp"


LightSensor::LightSensor(uint8_t pin)
   : pin_(pin)
{
   LOG_INFO("Initializing..,");

   pinMode(pin_, INPUT);
}


void
LightSensor::publish()
{
   LOG_INFO("Reading sensor");
   
   String value("/light/");
   value.concat(analogRead(pin_));
   gateway.publish(value);
}


