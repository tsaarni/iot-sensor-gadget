
#include <stdint.h>
#include <stdio.h>

#include <Arduino.h>
#include <Wire.h>
#include <ADS1115.h>
#include <RF24.h>
#include "printf.h"

#include "logging.hpp"


// mqtt topic to post the measured current transformer values
const char* topic = "current";


ADS1115 adc1(ADS1115_ADDRESS_ADDR_VDD);
ADS1115 adc2(ADS1115_ADDRESS_ADDR_GND);

RF24 radio(/* ce pin */ 9, /* cs pin */ 10);


void
register_node_to_gateway(const char* node_id)
{
   const uint8_t address[5] = { '1', 'm', 'q', 't', 't' };
   int timeout = 10000;

   LOG_INFO("starting radio...");
   radio.begin();
   radio.enableDynamicPayloads();
   radio.openWritingPipe(address);
   radio.printDetails();
   // radio.stopListening();


   return;


   bool registered = false;

   String reg_req("/register/");
   reg_req += node_id;

   while (registered == false)
   {
      LOG_INFO("sending: %s", reg_req.c_str());
      if (radio.write(reg_req.c_str(), reg_req.length()) == false)
      {
         LOG_ERROR("write failed, sleeping");
         delay(timeout);
         continue;
      }

      if (radio.available())
      {
         byte buf[32] = {0};
         LOG_INFO("reading response");
         radio.read(buf, sizeof(buf));
      }
   }


}


double
calc_rms(ADS1115* adc, uint8_t mux, unsigned int crossings, unsigned int timeout_ms)
{
   double sum = 0;
   unsigned int num_samples = 0;
   double prev_sample = 0;

   adc->setMultiplexer(mux);

   unsigned long start = millis();

   while ((crossings > 0) && ((millis() - start) < timeout_ms))
   {
      // read mV from A/D converter
      double sample = adc->getConversion() * ADS1115_MV_1P024;
      num_samples++;

      sum += sample * sample;

      // calculate points where sample sign changes when the sine wave crosses zero
      if (signbit(prev_sample) != signbit(sample))
      {
         crossings--;
      }
      prev_sample = sample;
   }

   return sqrt(sum / num_samples);
}


void
setup()
{
   Serial.begin(115200);
   printf_begin();

   register_node_to_gateway("");

   Wire.begin();
   adc1.initialize();
   adc2.initialize();

   if (adc1.testConnection() == false)
   {
      LOG_ERROR("connection to ADC1 failed");
   }

   if (adc2.testConnection() == false)
   {
      LOG_ERROR("connection to ADC2 failed");
   }

   adc1.setMode(ADS1115_MODE_CONTINUOUS);
   adc1.setGain(ADS1115_PGA_1P024);  // range +-1024 mVolts
   adc1.setRate(ADS1115_RATE_860);   // 860 samples per second

   adc2.setMode(ADS1115_MODE_CONTINUOUS);
   adc2.setGain(ADS1115_PGA_1P024);
   adc2.setRate(ADS1115_RATE_860);

   LOG_INFO("entering main loop...");
}

void
loop()
{
   //double ct1_mv = calc_rms(&adc1, ADS1115_MUX_P0_N1, 100, 5000);
   //double ct2_mv = calc_rms(&adc1, ADS1115_MUX_P2_N3, 100, 5000);
   //double ct3_mv = calc_rms(&adc2, ADS1115_MUX_P0_N1, 100, 5000);
   double ct1_mv = 1;
   double ct2_mv = 1;
   double ct3_mv = 1;

   String msg("/" + String(topic) + "?" + String(ct1_mv) + ";" + String(ct2_mv) + ";" + String(ct3_mv));

   LOG_INFO("sending: %s (len:%d)", msg.c_str(), msg.length());
   if (radio.write(msg.c_str(), msg.length(), 1) == false)
   {
      LOG_ERROR("there was no receiver for message");
   }
}
