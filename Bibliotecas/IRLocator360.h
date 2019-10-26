/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/14/2019*/
/*************************************************************************/

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