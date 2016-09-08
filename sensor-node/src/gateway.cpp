

#include "logging.hpp"
#include "gateway.hpp"



Gateway::Gateway(uint8_t ce, uint8_t cs, const char* topic_prefix)
   : radio_(ce, cs), topic_prefix_(topic_prefix)
{

}


void
Gateway::register_node(const char* node_id)
{
   LOG_INFO("registering node: %s", node_id);

   const uint8_t address[5] PROGMEM = { '1', 'm', 'q', 't', 't' };
   int timeout = 10000;
   
   radio_.begin();
   radio_.openWritingPipe(address);
   radio_.setPALevel(RF24_PA_LOW);

   bool registered = false;

   String reg_req("/register/");
   reg_req.concat(node_id);
   
   while (!registered)
   {
      LOG_INFO("sending: %s", reg_req.c_str());
      if (radio_.write(reg_req.c_str(), reg_req.length()) == false)
      {
         LOG_ERROR("write failed, sleeping");
         delay(timeout);
         continue;
      }

      if (radio_.available())
      {
         byte buf[32] = {0};
         LOG_INFO("reading response");
         radio_.read(buf, sizeof(buf));
      }
   }


   
}


void
Gateway::publish(const String& msg)
{   
   LOG_INFO("Publishing: %s", msg.c_str());
   radio_.write(msg.c_str(), msg.length() + 1);
}
