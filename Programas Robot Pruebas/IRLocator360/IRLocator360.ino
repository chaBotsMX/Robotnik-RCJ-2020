#include <IRLocator360.h>
IRLocator360 IR;
void setup() {
  Serial.begin(9600);
  IR.sensorInitialization();  
}

void loop() {
    Serial.println(IR.angleDirection600hz());
}
