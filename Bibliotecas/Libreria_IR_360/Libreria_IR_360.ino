/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Libreria IR Locator 360 ModernRobotics V 3.0                           */
/*https://modernroboticsinc.com/product/ir-locator-360/                  */
/*S.L.P MEXICO                           TIME:16:37:40 PM DATE:10/23/2019*/
/*************************************************************************/

/*
Direcciones de datos I2C
  0x00 Sensor Firmware Revision
  0x01 Manufacturer Code
  0x02 Sensor ID Code
  0x03 Not Used
  0x04 1200 Hz Heading in 5° increments
  0x05 1200 Hz Signal Strength
  0x06 600 Hz Heading in 5° increments
  0x07 600 Hz Signal Strength
Direccion I2C Arduino 7-Bit
  0x0E
Direccion I2c 8-Bit
  0x1C
*/

#include <Wire.h>

#define adress7bit 0x0E
#define adress8bit 0x1C
#define sensorfirmware 0x00
#define heading1200hz 0x04
#define signalstrength1200hz 0x05
#define heading600hz 0x06
#define signalstrength600hz 0x07

void sensorInitialization(){
  Wire.begin();
  Wire.beginTransmission(adress7bit);
  Wire.write(sensorfirmware);
  Wire.endTransmission();
}

int dataReturn(int i2c){
  Wire.beginTransmission(adress7bit);
  Wire.write(i2c);
  Wire.endTransmission();
  Wire.requestFrom(adress7bit,1);
  int head;
  if(Wire.available()<=1){  
    head=Wire.read();
  }
  if(head>355)
    head=-1;
  return head;
}

int angleDirection(){
  return dataReturn(heading600hz)*5;
}

int signalStrength(){
  return dataReturn(signalstrength1200hz);
}


void setup() {
  Serial.begin(9600);
  sensorInitialization();
}


int head;

void loop() {
  Serial.print(signalStrength());
  Serial.print("\t");
  Serial.println(angleDirection());
}
