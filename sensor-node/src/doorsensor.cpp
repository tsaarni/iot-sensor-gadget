
#include "logging.hpp"
#include "gateway.hpp"
#include "doorsensor.hpp"


static DoorSensor* self = nullptr;


void
interrupt_handler()
{
   LOG_INFO("Interrupt triggered");
   self->tripped();
}


DoorSensor::DoorSensor(uint8_t pin)
   : pin_(pin)
{
   LOG_INFO("Initializing...");
   
   pinMode(pin_, INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(pin_), interrupt_handler, CHANGE);
   self = this;

}

void 
DoorSensor::tripped()
{
   String state((digitalRead(pin_) == HIGH) ? "open" : "close");
   gateway.publish(state);
}

