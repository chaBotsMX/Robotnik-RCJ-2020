/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Libreria IR Locator 360 ModernRobotics V 0.1                           */
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
int heading1200hz =0x04;
int headindsignal1200hz =0x05;
int heading600hz=0x06;
int headindsignal600hz=0x07;

void inicializar_ir(){
  Wire.begin();
  Wire.beginTransmission(adress7bit);
  Wire.write(0x00);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(9600);
  inicializar_ir();
}

int head;

void loop() {
  Wire.beginTransmission(adress7bit);
  Wire.write(0x06);
  Wire.endTransmission();
  Wire.requestFrom(adress7bit,1);
  int head;
  if(Wire.available()<=1){
    head=Wire.read();
    
  }
  Serial.println(head*5);
}
