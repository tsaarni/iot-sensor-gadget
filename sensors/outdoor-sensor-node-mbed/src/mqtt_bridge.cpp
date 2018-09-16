

#include "mbed.h"
#include "mqtt_bridge.hpp"
#include "raii_char_str.hpp"
#include "logging.hpp"


// pinout: NRF24L01 module
//
//   IRQ  (NC)   MISO (PA6)
//   MOSI (PA7)  SCK  (PA5)
//   CSN  (PA4)  CE   (PA3)
//   VCC         GND
//


const PinName mosi = PA_7;
const PinName miso = PA_6;
const PinName sck  = PA_5;
const PinName csn  = PA_4;
const PinName ce   = PA_3;

MqttBridge::MqttBridge()
   : radio_(ce, csn)
{
}


void
MqttBridge::initialize()
{
   const uint8_t address[5] = { '1', 'm', 'q', 't', 't' };

   radio_.begin();
   radio_.openWritingPipe(address);
   radio_.enableDynamicPayloads();
   radio_.setCRCLength(RF24_CRC_16);
   radio_.setPALevel(RF24_PA_MAX);
   //radio_.printDetails();
   radio_.stopListening();
}


void
MqttBridge::publish(const std::string& topic, const std::string& msg)
{
   raii_char_str buf{"/" + topic + "?" + msg};
   radio_.powerUp();
   radio_.write(&buf[0], buf.size(), 1);
   radio_.powerDown();
}
