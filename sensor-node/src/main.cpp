

#include <Arduino.h>
#include <TimerOne.h>

#include "logging.hpp"
#include "gateway.hpp"
#include "htu32dsensor.hpp"
#include "doorsensor.hpp"
#include "lightsensor.hpp"


const char topic_prefix[] PROGMEM = "myhome";


Gateway gateway(/*ce*/  9, /*cs*/ 10, topic_prefix);
DoorSensor door(/*pin*/ 8);
LightSensor light(/*pin*/ 14);
Htu32dSensor temp_humid;


void
read_sensors()
{
   temp_humid.publish();
   light.publish();
}


void setup()
{
   Serial.begin(57600);
   Timer1.initialize(1000);
   Timer1.attachInterrupt(read_sensors);   
}


void loop()
{
   
}
