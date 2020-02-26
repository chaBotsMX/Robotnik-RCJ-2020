#include "Line_Sensor.h"
#define umbral 2700
#include <Adafruit_NeoPixel.h>
#define PIN 7
#define PIN2 6
#define PIN3 4
#define PIN4 3
#define NUMPIXELS 3 
#define intensidad 50
int sensorX[]={1,0,-1,0};
int sensorY[]={0,1,0,-1};
bool sensor[4];
int contador=0;
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixel(NUMPIXELS, PIN2, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pixe(NUMPIXELS, PIN3, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel pix(NUMPIXELS, PIN4, NEO_RGB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  analogReadResolution(12);
  pixels.begin();
  pixel.begin();
  pixe.begin();
  pix.begin();
  for(int i=0; i<NUMPIXELS; i++) { //GRB
    pixels.setPixelColor(i, pixels.Color(0, 50, 50));
    pixel.setPixelColor(i, pixels.Color(0, 50, 50));
    pixe.setPixelColor(i, pixels.Color(0, 50, 50));    
    pix.setPixelColor(i, pixels.Color(0, 50, 50));
    pix.show();    
    pixe.show();
	  pixels.show();
	  pixel.show(); 
	  pixe.show();  
	}
}

int angulo(){
    int angle=0;
    int sumax=0;
    int sumay=0;
    sensor[0]>0 ?  sumax = sumax + sensorX[0] : sumay= sumay + sensorY[0]; // 0
    sensor[1]>0 ?  sumay = sumay + sensorY[1] : sumax= sumax + sensorX[1]; // 90
    sensor[2]>0 ?  sumax = sumax + sensorX[2] : sumay= sumay + sensorY[2]; // 180
    sensor[3]>0 ?  sumay = sumay + sensorY[3] : sumax= sumax + sensorX[3]; // 270
    if(sumax!=0&&sumay!=0){
        angle=atan((sumay/sumax))*180.00/M_PI;
        if(angle<0){
            if(sensor[1])
                angle=angle+360;
            else
                angle=angle+180;
        }
        else {
           angle=angle+180;
      }
    }
    else{
        if(sumax==0&&sumay==0)
            angle=180;
       
      
    }
    return angle;
}
int angulo2(){
  int suma=0;
  int angle=0;
  contador=0;
  
int mov[]={180,270,0,90};
  
  for(int i=0; i<=3; i++){
        mov[2]=0;
        if(sensor[i]){
            contador > 1 ? mov[2]=0 : mov [2]=360;
            suma=suma+mov[i];
            contador++;
        }
    }
    angle=(suma/contador);
    
    return angle;
    
}

int ports[]={A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11};

bool isLine(int a, int b){
  for(int i=a; i<=b; i++){
    if(analogRead(ports[i])>=umbral)
      return true; 
  }
  return false;
}

void loop() {
  
  sensor[0]=isLine(3,5);//bien
  sensor[1]=isLine(0,2);
  sensor[2]=isLine(9,11);
   sensor[3]=isLine(6,8);
  Serial.print(sensor[0]); //ENFRENTE
  Serial.print("\t");
  Serial.print(sensor[1]); //DERECHA
  Serial.print("\t");
  Serial.print(sensor[2]); //ATRAS
  Serial.print("\t");
  Serial.print(sensor[3]); //IZQUIERDA
  Serial.print("\t");
  Serial.print(angulo2());
  Serial.print("\n");
}
