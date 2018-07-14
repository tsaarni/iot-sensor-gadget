
//#include <stdio.h>
#include "mbed.h"
#include "Adafruit_ADS1015.h"


I2C i2c(PB_7, PB_6);




Adafruit_ADS1015 ads1(&i2c, 0b1001000);
Adafruit_ADS1015 ads2(&i2c, 0b1001001);
Adafruit_ADS1015 ads3(&i2c, 0b1001010);

DigitalOut myled(PB_12);
Serial pc(PA_9, PA_10);

int
main(int argc, char *argv[])
{
   pc.printf("Foo\n");
   ads1.setGain(GAIN_SIXTEEN); // set range to +/-0.256V
   ads2.setGain(GAIN_SIXTEEN); // set range to +/-0.256V
   ads3.setGain(GAIN_SIXTEEN); // set range to +/-0.256V

   int r1, r2, r3;

   while(1) {
      r1 = ads1.readADC_SingleEnded(0);
      r2 = ads2.readADC_SingleEnded(0);
      r3 = ads3.readADC_SingleEnded(0);
      pc.printf("%d %d %d\n", r1, r2, r3);

      wait(1);
      myled = 1;
      wait(1);
      myled = 0;
   }
}
