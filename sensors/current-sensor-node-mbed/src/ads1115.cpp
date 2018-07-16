
#include "mbed.h"

#include "ads1115.hpp"
#include "logging.hpp"

#include <stdint.h>


const uint8_t ads_reg_conversion = 0b00;  // address of conversion register
const uint8_t ads_reg_config     = 0b01;  // address of config register


const uint16_t ads_config_pga_6144         = 0b000 << 9;  // programmable gain amplifier: range +-6.144V
const uint16_t ads_config_pga_4096         = 0b001 << 9;  // programmable gain amplifier: range +-4.096V
const uint16_t ads_config_pga_2048         = 0b010 << 9;  // programmable gain amplifier: range +-2.048V
const uint16_t ads_config_pga_1024         = 0b011 << 9;  // programmable gain amplifier: range +-1.024V
const uint16_t ads_config_dr_860sps        = 0b111 << 5;  // data rate: 860 samples per second
const uint16_t ads_config_comp_que_disable = 0b11;        // comparator: disable

const uint16_t ads_config_value = ads_config_pga_2048 | ads_config_dr_860sps | ads_config_comp_que_disable;

// const double ads_conversion_to_volts = 6.144 / INT16_MAX;
// const double ads_conversion_to_volts = 4.096 / INT16_MAX;
const double ads_conversion_to_volts = 2.048 / INT16_MAX;
// const double ads_conversion_to_volts = 1.024 / INT16_MAX;


Ads1115::Ads1115(I2C* i2c, int address)
   : i2c_(i2c), address_(address)
{
   LOG_INFO("Ads1115::Ads1115");
}


void
Ads1115::initialize()
{
   LOG_INFO("Ads1115::initialize");

   // write configuration
   char config[] = { ads_reg_config,
                     ads_config_value >> 8,
                     ads_config_value & 0xff };
   i2c_->write(address_<<1, config, sizeof(config));

   // prepare pointer register for reading A/D conversion register
   char pointer[] = { ads_reg_conversion };
   i2c_->write(address_<<1, pointer, sizeof(pointer));
}


double
Ads1115::read_conversion()
{
   char buf[2] = {0};
   i2c_->read(address_<<1, buf, sizeof(buf));
   int16_t conversion_result = (buf[0] << 8) + buf[1];
   return conversion_result * ads_conversion_to_volts;
}
