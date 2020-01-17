#include "HTInfraredSeeker.h"
#include "IRLocator360.h"
#include <Wire.h>

IRLocator360 IR;
int DirectionAngle(byte Direction){
  return Direction * 30 - 150;
}
void setup() {
  
  Serial.begin(9600);
  InfraredSeeker::Initialize();
  IR.sensorInitialization();  
}

void loop() {
  InfraredResult InfraredBall = InfraredSeeker::ReadAC();
   Serial.print(IR.signalStrength1200hz());
  Serial.print("\t");
  Serial.print(IR.angleDirection600hz());
  Serial.print("\t");

  Serial.print(InfraredBall.Direction);
  Serial.print("\t");
  Serial.print(DirectionAngle(InfraredBall.Direction));
  Serial.print("\t");
  Serial.println(InfraredBall.Strength);
  
  }
