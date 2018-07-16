
#pragma once
#include "mbed.h"


class Ads1115
{
public:
   Ads1115(I2C* i2c, int address);
   virtual ~Ads1115() {};

   void initialize();
   double read_conversion();

   static const int address_1 = 0b1001000;
   static const int address_2 = 0b1001001;
   static const int address_3 = 0b1001010;
   static const int address_4 = 0b1001011;

private:
   I2C* i2c_;
   int address_;

};
