/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Libreria IR Locator 360 ModernRobotics V 3.2                           */
/*https://modernroboticsinc.com/product/ir-locator-360/                  */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/14/2019*/
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

#include "Arduino.h"
#include "Wire.h"
#include "IRLocator360.h"

IRLocator360::IRLocator360() {}

int IRLocator360::sensorInitialization() {
	Wire.begin();
	Wire.beginTransmission(adress7bit);
	Wire.write(sensorfirmware);
	Wire.endTransmission();	
}

int IRLocator360::dataReturn(byte i2c) {
	Wire.beginTransmission(adress7bit);
	Wire.write(i2c);
	Wire.endTransmission();
	Wire.requestFrom(adress7bit, 1);
	int head;
	if (Wire.available() <= 1) {
		head = Wire.read();
	}
	return head;
}

int IRLocator360::angleDirection600hz() {
	return dataReturn(heading6hz) * 5;
}

int IRLocator360::signalStrength600hz() {
	return dataReturn(signalstrength6hz);
}

int IRLocator360::signalStrength1200hz() {
	return dataReturn(signalstrength12hz);
}

int IRLocator360::angleDirection1200hz() {
	return dataReturn(heading12hz) * 5;
}