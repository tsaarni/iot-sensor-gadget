
#pragma once

#include <optional>

#include "mbed.h"
#include "ads1115.hpp"

class CurrentTransformer
{
public:
   CurrentTransformer(const char* name, Ads1115* adc, int half_waves_to_measure=100);
   virtual ~CurrentTransformer() {};

   std::optional<double> calc_rms();


private:
   void initialize_();

   const char* name_;
   Ads1115* adc_;
   Timer timer_;

   int half_waves_to_measure_;

   int crossings_;
   double sum_;
   unsigned int num_samples_;
   double sample_prev_ = 0;
};
