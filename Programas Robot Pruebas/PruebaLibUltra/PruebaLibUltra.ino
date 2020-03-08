#include "UltrasonicoLib.h"
//triger echo
Ultrasonico br(6,5);
Ultrasonico br2(19,18);
//Ultrasonico br3(4,3);

void setup(){
  Serial.begin(9600);
  // put your setup code here, to run once:
  br2.PAU();
  br.PAU();
 delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=br2.VCM();  //atras
  int y=br.VCM(); //lado
  int res=y;
  y > 60 ? x=x-50: x=x-75;
      y > 60 ? y=92-y: y=60-y;
  double h=sqrt((x*x)+(y*y));
  double angulo=asin((y/h))*180.00/M_PI;
  Serial.print(h);
  Serial.print("\t");
  
  Serial.print(y);
  Serial.print("\t");
  Serial.print(180+angulo);
  Serial.print("\t");
  Serial.println(x);
}
