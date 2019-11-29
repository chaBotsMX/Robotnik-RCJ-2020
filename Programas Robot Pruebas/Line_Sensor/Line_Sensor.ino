#include <Line_Sensor.h>
#define umbral 500
#include <Adafruit_NeoPixel.h>
#define PIN 2
#define PIND 3
#define PINT 10
#define NUMPIXELS 3 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixel(NUMPIXELS, PIND, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixe(NUMPIXELS, PINT, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  pixels.begin();   
  pixel.begin();
  pixe.begin();
  pixels.clear();
  pixel.clear();
  pixe.clear();
  for(int i=0; i<NUMPIXELS; i++) { 
    //pixels.Color(i,0,55,55);// takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    pixel.setPixelColor(i, pixel.Color(50,0,50));
    pixe.setPixelColor(i,pixe.Color(50,0,50));
    pixels.show();   // Send the updated pixel colors to the hardware.
	pixel.show();
	pixe.show();
  }
}

byte portsS1[]={A0,A1,A2};

Line_Sensor S1(portsS1, umbral);

void loop() {
}
