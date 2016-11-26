
#pragma once


class LightSensor
{
public:
   LightSensor(uint8_t pin);
   void publish();
   
private:
   uint8_t pin_;
};
