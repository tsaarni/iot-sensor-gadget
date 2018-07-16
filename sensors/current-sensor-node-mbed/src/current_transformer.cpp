
#include <cmath>

#include "current_transformer.hpp"
#include "logging.hpp"

const int amps_per_volt = 30;


CurrentTransformer::CurrentTransformer(const char* name, Ads1115* adc, int half_waves_to_measure)
   : name_(name), adc_(adc), half_waves_to_measure_(half_waves_to_measure)
{
   LOG_INFO("CurrentTransformer::CurrentTransformer");
   initialize_();
}


std::optional<double>
CurrentTransformer::calc_rms()
{
   timer_.start();

   double sample_cur = adc_->read_conversion();
   num_samples_++;

   // calculate points where sample sign changes when the sine wave crosses zero
   if (std::signbit(sample_prev_) != std::signbit(sample_cur))
   {
      crossings_--;
   }

   sum_ += sample_cur * sample_cur;
   sample_prev_ = sample_cur;

   if ((crossings_ > 0) || (timer_.read_ms() < 1000))
   {
      // reasult not available since measurement is ongoing
      return std::nullopt;
   }


   double volts_rms = sqrt(sum_ / num_samples_);
   initialize_();
   LOG_INFO("%s: %f (%fA)", name_, volts_rms, volts_rms * amps_per_volt);
   return volts_rms;
}



void
CurrentTransformer::initialize_()
{
   // LOG_INFO("CurrentTransformer::initialize");

   crossings_ = half_waves_to_measure_;
   sum_ = 0;
   num_samples_ = 0;
   timer_.reset();
}
