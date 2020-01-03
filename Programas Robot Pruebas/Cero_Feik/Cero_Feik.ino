#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>
//3537
int ina[]={0,3,35,30};
int inb[]={0,14,37,32};
int pwm[]={0,8,7,6};



double targetRotation=0.0;
BNO080 myIMU;
DueFlashStorage dueFlashStorage;

double getFilter(double rot){
  double rt=rot;
  if(rt<=180)
    return rt/180.0;
  return (rt-360)/180.0;
}

double error(double rot){
    double err=360.00-rot;
    if(err>180.00)
      err=err-360.00;
    return err;    
}

double getRawRotation(){
  myIMU.dataAvailable();
  float x = myIMU.getQuatI();
  float y = myIMU.getQuatJ();
  float z = myIMU.getQuatK();
  float w = myIMU.getQuatReal();
  float quatRadianAccuracy = myIMU.getQuatRadianAccuracy();
  double siny_cosp = 2.0 * (w * z + x * y);
  double cosy_cosp = 1.0 - 2.0 * (y * y + z * z);
  return atan2(siny_cosp, cosy_cosp)*180.0/3.141592653;
}

double getRotation(){
  // Leer la rotacion en cuanto al Norte Magnetico del IMU
  double rot = getRawRotation();
  
  // Obtener la rotacion relativa al frente inicial (rotacion "0")
  double rt=rot-targetRotation;

  // Condiciones para asegurarnos de que el valor de rotacion
  // regresado (como resultado) por la funcion sea valido 
  // (entre 0 y 360).
  if(rt<0)
    rt+=360;
  if(rt>360)
    rt-=360;
  // Regresar la rotacion actual del robot
  return rt;
  
}

void setup() {
  Serial.begin(9600);  
  Wire.begin();
  myIMU.begin();
  myIMU.enableRotationVector(50);
  targetRotation=dueFlashStorage.read(0)+dueFlashStorage.read(1);
  pinMode(9,OUTPUT);
  pinMode(52,INPUT_PULLUP);
}

double escribir(double alineacion){
  alineacion > 0 ? alineacion=alineacion : alineacion=360.00+alineacion;
  if(alineacion>255){
    dueFlashStorage.write(0,255);
    dueFlashStorage.write(1,alineacion-255);
  }
  else {
    dueFlashStorage.write(0,0);
    dueFlashStorage.write(1,alineacion);
  } 
  return dueFlashStorage.read(0)+dueFlashStorage.read(1);
}

void loop() {
  if(!digitalRead(52)==1){
    targetRotation=escribir(getRawRotation());
  }  
  double mag=getRawRotation();
  if(mag<0)
    mag=360.00+mag;
    
  Serial.print(mag);
  Serial.print("\t");
  
  Serial.print(targetRotation);
  Serial.print("\t");
  Serial.println(error(getRotation()));
  //Serial.println(error(getRotation()));
  //Serial.println(getFilter(360.00-getRotation()));
  //Serial.println(erro);
}
