
#include "mbed.h"
#include "ads1115.hpp"
#include "current_transformer.hpp"
#include "logging.hpp"
#include "mqtt_bridge.hpp"

#include <string>


I2C i2c(PB_7,  // SDA
        PB_6); // SCL

DigitalOut activity_led(PB_12);

Ads1115 adc1(&i2c, Ads1115::address_1);
Ads1115 adc2(&i2c, Ads1115::address_2);
Ads1115 adc3(&i2c, Ads1115::address_3);

CurrentTransformer ct_phase1("phase 1", &adc1);
CurrentTransformer ct_phase2("phase 2", &adc2);
CurrentTransformer ct_phase3("phase 3", &adc3);

MqttBridge mqtt;


void
measure_loop()
{
   LOG_INFO("starting radio");
   mqtt.initialize();

   LOG_INFO("starting A/D converters");
   adc1.initialize();
   adc2.initialize();
   adc3.initialize();

   LOG_INFO("entering measurement loop");

   Timer timer_;
   double phase1_amps = 0;
   double phase2_amps = 0;
   double phase3_amps = 0;

   while (1) {

      timer_.start();

      auto phase1_volts_rms = ct_phase1.calc_rms();
      auto phase2_volts_rms = ct_phase2.calc_rms();
      auto phase3_volts_rms = ct_phase3.calc_rms();

      if  (phase1_volts_rms)
      {
         phase1_amps = *phase1_volts_rms * 30;
      }

      if  (phase2_volts_rms)
      {
         phase2_amps = *phase2_volts_rms * 30;
      }

      if  (phase3_volts_rms)
      {
         phase3_amps = *phase3_volts_rms * 30;
      }

      if (timer_.read_ms() > 1000)
      {
         activity_led = !activity_led;

         char msg[30];
         sprintf(msg, "%0.2f&%0.2f&%0.2f", phase1_amps, phase2_amps, phase3_amps);
         mqtt.publish("current", msg);

         phase1_amps = 0;
         phase2_amps = 0;
         phase3_amps = 0;
         timer_.reset();
      }

   }
}


int
main(int argc, char *argv[])
{
   LOG_INFO("Starting");

   measure_loop();
}
