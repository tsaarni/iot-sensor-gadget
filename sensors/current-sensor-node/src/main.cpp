
#include <Arduino.h>
#include <Wire.h>
#include <ADS1115.h>

ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);


double
calc_rms(unsigned int crossings, unsigned int timeout_ms)
{
    double sum = 0;
    unsigned int num_samples = 0;
    double prev_sample = 0;
    unsigned long start = millis();

    while ((crossings > 0) && ((millis() - start) < timeout_ms))
    {
        // read mV from A/D converter
        double sample = adc0.getConversionP0N1() * ADS1115_MV_1P024;
        num_samples++;

        sum += sample * sample;

        // calculate points where sample sign changes
        if (signbit(prev_sample) != signbit(sample))
        {
            crossings--;
        }
        prev_sample = sample;
    }

    return sqrt(sum / num_samples);
}


void
setup()
{
    Serial.begin(115200);

    Wire.begin();
    adc0.initialize();

    Serial.println(adc0.testConnection() ? "ADS1115 connection successful" : "ADS1115 connection failed");

    adc0.setMode(ADS1115_MODE_CONTINUOUS);
    adc0.setGain(ADS1115_PGA_1P024);  // range +-1024 mVolts
    adc0.setRate(ADS1115_RATE_860);  // 860 samples per second
}

void
loop()
{
    double millivolts = calc_rms(100, 5000);
    Serial.println(millivolts);
    //Serial.println(0.03*millivolts);
}
