#include "Line_Sensor.h"
#define umbral 2500
#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 3 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  pixels.begin();
  for(int i=0; i<NUMPIXELS; i++) { //GRB
    pixels.setPixelColor(i, pixels.Color(0, 50, 50));
    pixels.show();   // Send the updated pixe colors to the hardware.
	}
}

int portsS1[]={A1,A2,A3};

bool isLine(){
  for(int i=0; i<=2; i++){
    if(analogRead(portsS1[i])>=umbral)
      return true; 
  }
  return false;
}

Line_Sensor S1(portsS1, umbral);

void loop() {
  S1.SensorValue();
  Serial.println(isLine());
}
