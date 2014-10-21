#include <SoftwareSerial.h>

#include "Wire.h"
#define pHtoI2C 0x48

float voltage, data;
float pH;
byte highbyte, lowbyte, configRegister;

const int numReadings = 10;

float readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
float total = 0;                  // the running total
float average = 0;                // the average
void setup()
{
  Wire.begin();
  Serial.begin(9600);
  }
  
  void loop()
{
  // Чтение pH
  Wire.requestFrom(pHtoI2C, 3);
 while(Wire.available()) // ensure all the data comes in
 {
 highbyte = Wire.read(); // high byte * B11111111
 lowbyte = Wire.read(); // low byte
 configRegister = Wire.read();
 }

 data = highbyte * 256;
 data = data + lowbyte;

 voltage = data * 2.048 ;
 voltage = voltage / 327.68; // mV


 total= total - readings[index];
 readings[index] = ((-59.16 * voltage / (273.15 + 25)) + 7.0);
 total= total + readings[index];
 index = index + 1;
   // if we're at the end of the array...
  if (index >= numReadings)              
    // ...wrap around to the beginning: 
    index = 0;    
    average = total / numReadings;
    pH = average;
    
    Serial.println(pH);
    delay(500);
    }
