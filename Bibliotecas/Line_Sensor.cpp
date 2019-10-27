/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/27/2019*/
/*************************************************************************/

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Line_Sensor.h"


/*class LineSensor {
private:
	byte port[3];

public:
	bool isGreen() {
		for (int i = 0; i < 3; i++)
			if (analogRead(port[i]) >= 200)
				return false;
		return true;
	}

	LineSensor(byte port1, byte port2, byte port3) {
		port[0] = port1;
		port[1] = port2;
		port[2] = port3;
	}
};
*/