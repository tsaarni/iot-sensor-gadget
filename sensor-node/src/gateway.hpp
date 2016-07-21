
#pragma once


#include <RF24.h>


class Gateway
{
public:
   Gateway(uint8_t ce, uint8_t cs, const char* topic_prefix);
   void set_node_id(uint16_t node_id);
   void publish(const String& msg);
      
private:
   RF24 radio_;
   const char* topic_prefix_;
};


extern Gateway gateway;

