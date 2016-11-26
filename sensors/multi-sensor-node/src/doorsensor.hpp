
#pragma once


class DoorSensor
{
public:
   DoorSensor(uint8_t pin);   
   void tripped();
   
private:
   uint8_t pin_;
};


