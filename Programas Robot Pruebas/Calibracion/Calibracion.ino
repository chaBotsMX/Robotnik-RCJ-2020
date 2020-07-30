#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>

const int magx = -8;
const int magy = -6;

double targetRotation=0.0;
BNO080 myIMU;
DueFlashStorage dueFlashStorage;


void setup() {
  Serial.begin(9600);  
  Wire.begin();
  myIMU.begin();
  myIMU.enableMagnetometer(50);
  delay(20);
}


int t=0;
float minx=0;
  float maxx=0;
  float miny=0;
  float maxy=0;
void loop() {
  
  float offsetx;
  float offsety;
  myIMU.dataAvailable();
  
    
    float x = myIMU.getMagX();
    float y = myIMU.getMagY();
    float z = myIMU.getMagZ();
    float angle = atan2(x, y)*180.00/M_PI;
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.print(x-magx);
    Serial.print("\t");
    Serial.print(y-magy);
    Serial.print("\t");
    Serial.print(angle);
    Serial.print("\n");
   
}
