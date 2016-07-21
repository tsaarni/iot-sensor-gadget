

#include "logging.hpp"
#include "gateway.hpp"



Gateway::Gateway(uint8_t ce, uint8_t cs, const char* topic_prefix)
   : radio_(ce, cs), topic_prefix_(topic_prefix)
{
   LOG_INFO("Initializing...");
   const uint8_t address[5] PROGMEM = { '1', 'm', 'q', 't', 't' };

   radio_.begin();
   radio_.openWritingPipe(address);
   radio_.setPALevel(RF24_PA_LOW);
}


void
Gateway::set_node_id(uint16_t node_id)
{
   LOG_INFO("setting node id");
   LOG_INFO(node_id);

   bool registered = false;
   byte buf[32] = {0};
   
   whilte (registered)
   {
      registered = radio.writeBlocking();
      
      if (registered == true && radio.available())
      {
         radio.read(buf, sizeof(buf));
      }
   }


   
}


void
Gateway::publish(const String& msg)
{   
   LOG_INFO("Publishing:");
   LOG_INFO(msg.c_str());
   radio_.write(msg.c_str(), msg.length() + 1);
}
