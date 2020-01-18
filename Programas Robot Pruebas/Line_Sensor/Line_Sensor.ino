#include "Line_Sensor.h"
#define umbral 2700
#include <Adafruit_NeoPixel.h>
#define PIN 7
#define NUMPIXELS 3 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  pixels.begin();
  for(int i=0; i<NUMPIXELS; i++) { //GRB
    pixels.setPixelColor(i, pixels.Color(0, 50, 50));
    pixels.show();   // Send the updated pixe colors to the hardware.
	}
}

int portsS1[]={A0,A1,A2};

bool isLine(){
  for(int i=0; i<=2; i++){
    if(analogRead(portsS1[i])>=umbral)
      return true; 
  }
  return false;
}

Line_Sensor S1(portsS1, umbral);

void loop() {

  /*Serial.print(analogRead(A0));
  Serial.print("\t");
  Serial.print(analogRead(A1));
  Serial.print("\t");
  Serial.print(analogRead(A2));
  Serial.print("\n");  
 */ Serial.println(isLine());
}
