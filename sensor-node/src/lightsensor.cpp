
#include "logging.hpp"
#include "gateway.hpp"
#include "lightsensor.hpp"


LightSensor::LightSensor(uint8_t pin)
   : pin_(pin)
{
   LOG_INFO(PSTR("Initializing..,"));

   pinMode(pin_, INPUT);
}


void
LightSensor::publish()
{
   LOG_INFO(PSTR("Reading sensor"));
   
   String value(PSTR("/light/"));
   value.concat(analogRead(pin_));
   gateway.publish(value);
}


