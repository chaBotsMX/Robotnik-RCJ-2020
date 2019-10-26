#include <IRLocator360.h>
IRLocator360 xd;
void setup() {
 Serial.begin(9600);
xd.sensorInitialization();  
}

void loop() {
    Serial.println(xd.angleDirection600hz());
}
