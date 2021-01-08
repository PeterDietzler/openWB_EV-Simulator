#include <Wire.h>
#include <Adafruit_ADS1015.h>

//#include "hardware.h"

Adafruit_ADS1115 ads( 0x48);  //ADS1015_I2C_ADR);

float Voltage = 0.0;

int initMeasurVoltage(int Address)
{
  //ads.begin();

}



long MeasureVoltage( uint8_t channel) 
{
  int16_t adc0;
  
  adc0 = ads.readADC_SingleEnded( channel);
  Voltage = (adc0 * 0.1875)/1000;
  return Voltage;
}
