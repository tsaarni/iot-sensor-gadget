


#include "logging.hpp"
#include "gateway.hpp"
#include "htu32dsensor.hpp"


Htu32dSensor::Htu32dSensor()
{
   LOG_INFO("Initializing...");
   htu_.begin();
}


void
Htu32dSensor::publish()
{
   LOG_INFO("Reading sensor");
   
   String temp("/temp/");
   String humid("/humid/");

   temp.concat(htu_.readTemperature());
   humid.concat(htu_.readHumidity());
   
   gateway.publish(temp);
   gateway.publish(humid);
}

