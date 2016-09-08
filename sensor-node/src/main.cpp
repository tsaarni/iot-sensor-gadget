

#include <Arduino.h>

#include <TimerOne.h>

#include "logging.hpp"
#include "gateway.hpp"
#include "nodeid.hpp"

#include "htu32dsensor.hpp"
#include "doorsensor.hpp"
#include "lightsensor.hpp"
#include "batterysensor.hpp"


const char topic_prefix[] PROGMEM = "myhome";
const int random_seed_pin PROGMEM = A3;

Gateway gateway(/*ce*/  9, /*cs*/ 10, topic_prefix);
NodeId node_id;

// sensors
//DoorSensor door(/*pin*/ 8);
//LightSensor light(/*pin*/ 14);
//Htu32dSensor temp_humid;
//BatterySensor battery;

void
read_sensors()
{
   //temp_humid.publish();
   //light.publish();
   //battery.publish();
}


void setup()
{
   Serial.begin(57600);
   LOG_INFO("starting");

   // seed pseudo-random algorithm with unconnected analog pin 
   pinMode(random_seed_pin, INPUT);
   delay(10);
   randomSeed(analogRead(random_seed_pin) * analogRead(random_seed_pin));

   // restore pull-up to limit current leakage
   pinMode(random_seed_pin, INPUT_PULLUP);

   const char* node = node_id.get();
   
   gateway.register_node(node);
   
   //Timer1.initialize(1000);
   //   Timer1.attachInterrupt(read_sensors);   
}


void loop()
{
   
}
