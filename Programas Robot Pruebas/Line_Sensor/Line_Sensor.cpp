/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Line Sensor V1.0														 */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:10/27/2019*/
/*************************************************************************/

#include "Arduino.h"
#include "Line_Sensor.h"

Line_Sensor::Line_Sensor(int port[], int umbral) {
  for (int i = 0; i <=2; i++)
		_port[i] = port[i];
	_umbral = umbral;
}

bool Line_Sensor::isLine() {
	for (int i = 0; i <=2; i++)
		if (analogRead(_port[i]) >= _umbral)
			return true;
	return false;
}

void Line_Sensor::SensorValue(){
	Serial.print(analogRead(_port[0]));
	Serial.print("\t");
	Serial.print(analogRead(_port[1]));
	Serial.print("\t");
	Serial.print(analogRead(_port[2]));
	Serial.print("\n");
}
