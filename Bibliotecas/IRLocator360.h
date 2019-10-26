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

#ifndef IRLocator360_h
#define IRLocator360_h

#include "Arduino.h"

class IRLocator360{
	public:
		IRLocator360();
		int sensorInitialization();
		int dataReturn(byte i2c);
		int angleDirection600hz();
		int signalStrength600hz();
		int angleDirection1200hz();
		int signalStrength1200hz();
	private:
		const int adress7bit=0x0E;
		const int adress8bit=0x1C;
		const int sensorfirmware=0x00;
		const int heading12hz=0x04;
		const int signalstrength12hz=0x05;
		const int heading6hz=0x06;
		const int signalstrength6hz=0x07;
};

#endif