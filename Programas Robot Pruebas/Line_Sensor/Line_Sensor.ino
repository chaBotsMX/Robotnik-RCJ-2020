#include <Adafruit_NeoPixel.h>
#define PIN        8 // On Trinket or Gemma, suggest changing this to 1
#define NUMPIXELS 3 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  
  
  
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

     //pixels.Color(0,255,0);// takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
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
