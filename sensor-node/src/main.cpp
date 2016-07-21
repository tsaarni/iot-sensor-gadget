

#include <Arduino.h>
#include <EEPROM.h>

#include <TimerOne.h>

#include "logging.hpp"
#include "gateway.hpp"
#include "htu32dsensor.hpp"
#include "doorsensor.hpp"
#include "lightsensor.hpp"


const char topic_prefix[] PROGMEM = "myhome";


const int random_seed_pin = A3;

Gateway gateway(/*ce*/  9, /*cs*/ 10, topic_prefix);
DoorSensor door(/*pin*/ 8);
LightSensor light(/*pin*/ 14);
Htu32dSensor temp_humid;





void
initialize_unique_node_id()
{
   uint16_t node_id = EEPROM[0] << 8 | EEPROM[1];

   if (node_id == 0xffff)
   {
      pinmode(random_seed_pin, INPUT);
      randomSeed(analogRead(random_seed_pin));

      node_id = random(255) << 8 | random(255);

      EEPROM[0] = node_id >> 8 & 0xff;
      EEPROM[1] = node_id      & 0xff;
   }

   gateway.set_node_id(node_id);
}


void
read_sensors()
{
   temp_humid.publish();
   light.publish();
}


void setup()
{
   Serial.begin(57600);

   initialize_unique_node_id();
   
   Timer1.initialize(1000);
   Timer1.attachInterrupt(read_sensors);   
}


void loop()
{
   
}
