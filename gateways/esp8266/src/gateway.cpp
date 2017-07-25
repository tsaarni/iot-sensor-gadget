

#include "logging.hpp"
#include "gateway.hpp"


Gateway::Gateway(uint8_t cs_pin, uint8_t ce_pin)
   : cs_pin_(cs_pin), ce_pin_(ce_pin)
{
   
}


Gateway::init()
{

}

Gateway::loop()
{
   memset(buf, 0, sizeof(buf));
   uint8_t recv_bytes = radio_.getPayloadSize();
   radio_.read(buf, recv_bytes);
}
