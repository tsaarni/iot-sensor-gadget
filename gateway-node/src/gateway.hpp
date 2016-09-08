
#pragma once

#include <RF24.h>


class Gateway
{
public:
   Gateway(uint8_t cs_pin, uint8_t ce_pin);
   
private:
   const uint8_t address[5] = { '1', 'm', 'q', 't', 't' };
   static byte buf[32] = {0};
   
   RF24 radio_;
   uint8_t cs_pin_;
   uint8_t ce_pin_;
};
