#include "IRLocator360.h"
IRLocator360 IR;

void setup() {
  Serial.begin(9600);
  IR.sensorInitialization();  
}

void loop() {
  Serial.print(IR.signalStrength1200hz());
  Serial.print("\t");
  Serial.println(IR.angleDirection600hz());
}
