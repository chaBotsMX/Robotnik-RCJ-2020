/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Line Sensor V1.0														 */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/27/2019*/
/*************************************************************************/

#include "Arduino.h"
#include "Adafruit_NeoPixel.h"
#include "Line_Sensor.h"

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Line_Sensor::Line_Sensor(byte port[], int umbral, byte pinNeopixel) {
	for (int i = 0; i < 3; i++)
		_port[i] = port[i];
	_umbral = umbral;
	_pinNeopixel = pinNeopixel;
	pixels.begin();   
}

bool Line_Sensor::inLine() {
	for (int i = 0; i < 3; i++)
		if (analogRead(_port[i]) >= _umbral)
			return true;
	return false;
}

void Line_Sensor::setColor(byte r, byte g, byte b) {
	pixels.Color(_r, _g, _b);
	pixels.show();   
}

void Line_Sensor::itsMomentToFun(byte r, byte g, byte b) {
	for(int i=0; i<numPixels; i++){ 
		pixels.setPixelColor(i, pixels.Color(_r, _b, _b));
		pixels.show();
	}
}
