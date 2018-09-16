#include "mbed.h"

//#define LOG_NDEBUG 1
#include "logging.hpp"

#include "htu21d.h"
#include "mqtt_bridge.hpp"
#include "lowpower.hpp"

DigitalOut activity_led(PB_12);

htu21d htu(PB_7,   // SDA
           PB_6);  // SCL

//AnalogIn photocell(15);

// I2C i2c(PB_7, PB_6);

const uint8_t htu_userreg_end_of_battery = (1 << 6);

MqttBridge mqtt;

int
main(int argc, char *argv[])
{
   LOG_INFO("starting");
   wait(5);

   if (htu.softReset() == 0)
   {
      LOG_INFO("error resetting HTU21D");
   }

   mqtt.initialize();

   char msg[32];

   float humidity      = htu.getHum();
   float temperature   = htu.getTemp();
   float dew_point     = htu.getDewPtFast();
   bool end_of_battery = htu.getUserReg() & htu_userreg_end_of_battery;

   // LOG_INFO("temp: %.2fC, humidity: %.2f%% dew point: %.2fC end of battery: %s",
   //          temperature, humidity, dew_point, end_of_battery ? "true" : "false");

   sprintf(msg, "%.2f&%.2f&%.2f&%d",
           temperature, humidity, dew_point, end_of_battery ? 1 : 0);

   mqtt.publish("outside", msg);

   // activity_led = !activity_led;

   enter_standy(0,5,0);

   return 0;
}
