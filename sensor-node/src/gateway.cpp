

#include "logging.hpp"
#include "gateway.hpp"



Gateway::Gateway(uint8_t ce, uint8_t cs, const char* topic_prefix)
   : radio_(ce, cs), topic_prefix_(topic_prefix)
{
   LOG_INFO(PSTR("Initializing..."));
   const uint8_t address[5] PROGMEM = { '1', 'm', 'q', 't', 't' };

   radio_.begin();
   radio_.openWritingPipe(address);
   radio_.setPALevel(RF24_PA_LOW);
}


void
Gateway::register_node(const char* node_id)
{
   LOG_INFO(PSTR("setting node id"));
   LOG_INFO(node_id);

   bool registered = false;
   byte buf[32] = {0};
   
   while (registered)
   {
      registered = radio_.writeBlocking(buf, sizeof(buf), 1000);
      
      if (registered == true && radio_.available())
      {
         radio_.read(buf, sizeof(buf));
      }
   }


   
}


void
Gateway::publish(const String& msg)
{   
   LOG_INFO(PSTR("Publishing:"));
   LOG_INFO(msg.c_str());
   radio_.write(msg.c_str(), msg.length() + 1);
}
