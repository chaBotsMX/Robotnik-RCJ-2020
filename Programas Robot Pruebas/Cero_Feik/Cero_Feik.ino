#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>
//3537
int ina[]={0,3,35,30};
int inb[]={0,14,37,32};
int pwm[]={0,8,7,6};

const int magx = 17;
const int magy = 14;

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

double mag(){
  myIMU.dataAvailable();
  float x = myIMU.getMagX();
  float y = myIMU.getMagY();
  float z = myIMU.getMagZ();
  float angle = atan2(x-magx, y-magy)*180.00/M_PI;
  return angle;
}

double Set=0;

double getRotation(){
  // Leer la rotacion en cuanto al Norte Magnetico del IMU
  double rot=0;
  
  Set < 0 ? rot=360.00+Set : rot = Set;
  
  // Obtener la rotacion relativa al frente inicial (rotacion "0")
  double rt=rot+getRawRotation();

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
  bool im;
  Serial.begin(9600);  

  Serial.println("-----------------------------------");
  Wire.begin();
  myIMU.begin();
  myIMU.enableRotationVector(50);
  myIMU.enableMagnetometer(50);
  while(millis()<600){
    targetRotation=dueFlashStorage.read(3)+dueFlashStorage.read(4)*255;
    Serial.print(targetRotation);
    Serial.print("\t");
    Serial.println(mag());
    Set=getRawRotation()+(targetRotation-mag());
    delay(20);
  }
  pinMode(9,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  delay(20); //CAMBIAR A MILLIS
}


double escribir(int alineacion){
  dueFlashStorage.write(3, alineacion%255);
  dueFlashStorage.write(4, alineacion/255);
  delay(50);
}

double magn;  
void loop() {
  magn=mag();
  double erro = getRawRotation() - Set;
  
  erro < 0 ? erro = 360.00 + erro : erro=erro;  
  
  if(!digitalRead(8)==1){
    magn > 0 ? magn=magn : magn=360.00+magn;
    Serial.println(magn);
    escribir(magn);
    
    Set=getRawRotation();
    //Serial.println(magn);
  }  
  
  Serial.print(magn);
  Serial.print("\t");

  Serial.print(Set);
  Serial.print("\t");

  Serial.print(getRotation());
  Serial.print("\t");
   
  Serial.print(targetRotation);
  Serial.print("\t");
  Serial.println(erro);
  delay(20);
}
