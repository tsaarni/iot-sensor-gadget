

#include <Arduino.h>

#include "logging.hpp"
#include "gateway.hpp"
#include "batterysensor.hpp"


void
BatterySensor::publish()
{
   LOG_INFO("reading voltage level");

   // from http://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

   ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);

   delay(2); // Wait for Vref to settle
   ADCSRA |= _BV(ADSC); // Start conversion

   while (bit_is_set(ADCSRA,ADSC)); // measuring

   uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
   uint8_t high = ADCH; // unlocks both

   long result = (high<<8) | low;

   result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000

   String value("/bat/");
   value.concat(result);
   gateway.publish(value);
}
