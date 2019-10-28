#include <Adafruit_NeoPixel.h>
#define PIN        8 
#define NUMPIXELS 3 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)  
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
     //pixels.Color(0,255,0);
      pixels.setPixelColor(i, pixels.Color(100,   0 , 100));
      pixels.show();   
  }
}

void loop() {
  Serial.print(analogRead(A8)>700);
  Serial.print("\t");
  Serial.print(analogRead(A9)>700);
  Serial.print("\t");
  Serial.println(analogRead(A10)>700);
  
}
