#include "UltrasonicoLib.h"
//triger echo

Ultrasonico us1(4,3); //derecha
Ultrasonico us2(6,5); //izquierda 
Ultrasonico us3(19,18); //atras

void setup(){
  Serial.begin(9600);
  // put your setup code here, to run once:
  us1.PAU();
  us2.PAU();
  us3.PAU();
 delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=us3.VCM();  //atras
  int y=us2.VCM(); //izquierda
  int z=us1.VCM(); //derecha
  bool lado;
  lado = y > z ? 1 : 0;
  
  
  if(lado){
    y > 60 ? x=x-50: x=x-75;
    double h=sqrt((x*x)+(y*y));
    double angulo=asin((y/h))*180.00/M_PI;
    Serial.print("Derecha");
    Serial.print("\t");
    Serial.print(180+angulo);
  
  }
  else {
    z > 60 ? x=x-50: x=x-75;
    double h=sqrt((x*x)+(y*y));
    double angulo=asin((y/h))*180.00/M_PI;
    Serial.print("Izquierda");
    Serial.print("\t");
    Serial.print(180-angulo);
  
  }
  Serial.print("\t");
 
  //Serial.print("\t");
 
  Serial.print(z);
  Serial.print("\t");
  
  Serial.print(y);
  Serial.print("\t");
  //Serial.print(180+angulo);
  Serial.println(x);
}
