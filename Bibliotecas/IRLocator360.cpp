/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/14/2019*/
/*************************************************************************/

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