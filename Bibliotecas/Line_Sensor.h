/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Line Sensor V1.0														 */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/27/2019*/
/*************************************************************************/

#ifndef Line_Sensor_h
#define Line_Sensor_h

#include "Arduino.h"
//#include <Adafruit_NeoPixel.h>

//Adafruit_NeoPixel pixels(pinNeopixel, numPixels, NEO_GRB + NEO_KHZ800);

class Line_Sensor{
	public:
		Line_Sensor(int port[], int umbral);
		bool isLine();
		void SensorValue();
	//	void setColor(byte r, byte g, byte b);
		//void itsMomentToFun(byte r, byte g, byte b);
	private:
		int _umbral;
		byte _port[];
};


#endif
