#include "mbed.h"

#define LOG_NDEBUG
#include "logging.hpp"

#include "htu21d.h"
#include "mqtt_bridge.hpp"

DigitalOut activity_led(PB_12);

htu21d htu(PB_7,   // SDA
           PB_6);  // SCL

//AnalogIn photocell(15);

// I2C i2c(PB_7, PB_6);

const uint8_t htu_userreg_end_of_battery = (1 << 6);

//MqttBridge mqtt;

extern serial_t   stdio_uart;
extern int        stdio_uart_inited;

void
stdout_to_serial()
{
   serial_init(&stdio_uart, /* tx */ PA_9, /* rx */ PA_10);
   stdio_uart_inited = 1;
   serial_baud(&stdio_uart, 115200);
}


int
main(int argc, char *argv[])
{
   stdout_to_serial();

   LOG_INFO("starting");

   // LOG_INFO("RUN");
   // for(int i = 0; i < 128 ; i++) {
   //    i2c.start();
   //    if (i2c.write(i << 1) ==)
   //    {
   //       LOG_INFO("0x%x ACK",i);
   //    }
   //    i2c.stop();
   // }


   if (htu.softReset() == 0)
   {
      LOG_INFO("error resetting HTU21D");
   }

   char msg[32];

   while (true)
   {
      float humidity      = htu.getHum();
      float temperature   = htu.getTemp();
      float dew_point     = htu.getDewPtFast();
      bool end_of_battery = htu.getUserReg() & htu_userreg_end_of_battery;

      LOG_INFO("temp: %.2fC, humidity: %.2f%% dew point: %.2fC end of battery: %s",
               temperature, humidity, dew_point, end_of_battery ? "false" : "true");

      sprintf(msg, "t%.2f&h%.2f&%d.2f&b%d",
              temperature, humidity, dew_point, end_of_battery ? 1 : 0);

      
      //    mqtt.publish("outside", msg);

      activity_led = !activity_led;
      wait(1);
   }


   return 0;
}
