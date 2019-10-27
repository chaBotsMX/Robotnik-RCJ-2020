#include <Adafruit_NeoPixel.h>
#define PIN        8 
#define NUMPIXELS 3 

void setup() {
  Serial.begin(9600);
  pixels.begin(); 
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(100,   0 , 100));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
}

void loop() {
  Serial.print(analogRead(A8)>700);
  Serial.print("\t");
  Serial.print(analogRead(A9)>700);
  Serial.print("\t");
  Serial.println(analogRead(A10)>700);  
}
