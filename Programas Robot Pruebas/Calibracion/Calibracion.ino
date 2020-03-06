#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>

const int magx = -100;
const int magy = -140;

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



void loop() {
  myIMU.dataAvailable();
  float x = myIMU.getMagX();
  float y = myIMU.getMagY();
  float z = myIMU.getMagZ();
  float angle = atan2(x-magx, y-magy)*180.00/M_PI;
  Serial.print(angle);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\n");
}
