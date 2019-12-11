#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>

double targetRotation=0.0;
BNO080 myIMU;

double getFilter(double rot){
  double rt=rot;
  if(rt<=180)
    return rt/180.0;
  return (rt-360)/180.0;
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

void setup() 
{
  Serial.begin(9600);  
  Wire.begin();
  
  myIMU.begin();
  myIMU.enableRotationVector(50);
  while(millis()<600){
    targetRotation=getRawRotation();
  }
    
}
void loop() {
  Serial.println(360.00-getRotation());
}
