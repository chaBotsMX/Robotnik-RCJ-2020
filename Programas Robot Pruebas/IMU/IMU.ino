#include <Wire.h>

#include "SparkFun_BNO080_Arduino_Library.h"
BNO080 myIMU;

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.println("BNO080 Read Example");
  Wire.begin();
  if (myIMU.begin() == false){
    Serial.println("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }
  Wire.setClock(400000); //Increase I2C data rate to 400kHz
  myIMU.enableRotationVector(50); //Send data update every 50ms
  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form i, j, k, real, accuracy"));
}
float euler[3];
void loop(){
  if (myIMU.dataAvailable() == true){
    float q1 = myIMU.getQuatI(); //x
    float q2 = myIMU.getQuatJ(); //y
    float q3 = myIMU.getQuatK(); //z
    float q0 = myIMU.getQuatReal();
    float quatRadianAccuracy = myIMU.getQuatRadianAccuracy();
    euler[0] = -atan2(2 * q1 * q3 + 2 * q2 * q0, 1 - 2 * q1*q1 - 2 * q2 * q2)*180/PI; //pitch
    euler[1] = asin(2 * q2 * q3 - 2 * q1 * q0)*180/PI;  //row
    euler[2] = -atan2(2 * q1 * q2 + 2 * q3 * q0, 1 - 2 * q2 * q2 - 2 * q3 * q3)*180/PI; //yaw
    /*Serial.print(quatI, 2);
    Serial.print(F(","));
    Serial.print(quatJ, 2);
    Serial.print(F(","));
    Serial.print(quatK, 2);
    Serial.print(F(","));
    Serial.print(quatReal, 2);
    Serial.print(F(","));
*/  Serial.print(quatRadianAccuracy, 2);
    Serial.print(F(","));
    Serial.print(euler[0]);
    Serial.print("\t");
    Serial.print(euler[1]);
    Serial.print("\t");
    Serial.print(euler[2]);
    Serial.println();
  }
}
