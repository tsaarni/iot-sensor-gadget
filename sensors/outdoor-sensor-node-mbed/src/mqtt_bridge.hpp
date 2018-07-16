
#pragma once

#include "RF24.h"
#include <string>

class MqttBridge
{
public:
   MqttBridge();
   virtual ~MqttBridge() {};
   void initialize();
   void publish(const std::string& topic, const std::string& msg);

private:
   RF24 radio_;
};
