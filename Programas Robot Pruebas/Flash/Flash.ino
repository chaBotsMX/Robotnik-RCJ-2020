/* This example will write 3 bytes to 3 different addresses and print them to the serial monitor.
   Try resetting the Arduino Due or unplug the power to it. The values will stay stored. */

#include <DueFlashStorage.h>
DueFlashStorage dueFlashStorage;

void escribir(int alineacion){
  
  /*if(alineacion>255){
        dueFlashStorage.write(3, 255);
    dueFlashStorage.write(4, alineacion-255);
  }
  else{
    dueFlashStorage.write(3, alineacion);
    dueFlashStorage.write(4, 0);
  }*/
  dueFlashStorage.write(3, alineacion%255);
  dueFlashStorage.write(4, alineacion/255);
  delay(50);
}

void setup() {
  Serial.begin(115200);
pinMode(52,INPUT_PULLUP); 
}

void loop() {
  if(!digitalRead(52))
    escribir(220);
  else
    Serial.println(dueFlashStorage.read(3)+dueFlashStorage.read(4)*255);
  delay(1000);
}
