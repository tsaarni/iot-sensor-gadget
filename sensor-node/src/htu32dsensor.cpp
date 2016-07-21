


#include "logging.hpp"
#include "gateway.hpp"
#include "htu32dsensor.hpp"


Htu32dSensor::Htu32dSensor()
{
   LOG_INFO(PSTR("Initializing..."));
   htu_.begin();
}


void
Htu32dSensor::publish()
{
   LOG_INFO(PSTR("Reading sensor"));
   
   String temp(PSTR("/temp/"));
   String humid(PSTR("/humid/"));

   temp.concat(htu_.readTemperature());
   humid.concat(htu_.readHumidity());
   
   gateway.publish(temp);
   gateway.publish(humid);
}

