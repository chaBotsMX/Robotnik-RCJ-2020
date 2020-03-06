#include "UltrasonicoLib.h"
//triger echo
Ultrasonico br(6,5);
//Ultrasonico br2(19,18);
//Ultrasonico br3(4,3);

void setup(){
  Serial.begin(9600);
  // put your setup code here, to run once:
  //pinMode(17,OUTPUT);
  br.PAU();
  //br2.PAU();
  //br3.PAU();
 delay(20);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x=br.VCM();
  //int y=br2.VCM();
  //int z=br3.VCM();
  //int z=br3.VCM();
  //Serial.print(y);
  //Serial.print("\t");
  //Serial.print(z);
  //Serial.print(z);
  //Serial.print("\t");
  Serial.println(x);
}
