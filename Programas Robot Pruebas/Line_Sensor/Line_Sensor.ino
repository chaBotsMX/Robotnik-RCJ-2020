#include <Line_Sensor.h>
#define umbral 500
#include <Adafruit_NeoPixel.h>
#define PIN        2 
#define NUMPIXELS 3 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)  
  for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
     //pixels.Color(0,255,0);
pixels.setPixelColor(i, pixels.Color(50,   0 , 50));
pixels.show();   
  }
}

byte portsS1[]={A0,A1,A2};

Line_Sensor S1(portsS1, umbral);

void loop() {
  Serial.println(analogRead(A0));
  
}
