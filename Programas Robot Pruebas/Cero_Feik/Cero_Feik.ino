#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>
//3537
int ina[]={0,3,35,30};
int inb[]={0,14,37,32};
int pwm[]={0,8,7,6};

const int magx = 10;
const int magy = 5;

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
  Wire.begin();
  Wire.setClock(400000); //Increase I2C data rate to 400kHz
  im=myIMU.begin();
  if (!im)
  {
    Serial.println("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }
  else 
    myIMU.softReset();
  if(im){
    myIMU.enableRotationVector(50);
    myIMU.enableMagnetometer(50);
    targetRotation=dueFlashStorage.read(0)+dueFlashStorage.read(1);
    Set=getRawRotation()+(targetRotation-getRotation());
  }
  pinMode(9,OUTPUT);
  pinMode(52,INPUT_PULLUP);
  delay(20); //CAMBIAR A MILLIS
}


double escribir(double alineacion){
  targetRotation=alineacion;
  alineacion > 0 ? alineacion=alineacion : alineacion=360.00+alineacion;
  if(alineacion>=255){
    dueFlashStorage.write(0,255);
    dueFlashStorage.write(1,alineacion-255);
  }
  else {
    dueFlashStorage.write(0,alineacion);
    dueFlashStorage.write(1,0);
  } 
}
double magn;  
void loop() {
  magn=mag();
  double erro = getRawRotation() - Set;
  
  erro < 0 ? erro= 360.00+erro : erro=erro;  
  
  if(!digitalRead(52)==1){
    escribir(magn);
    Set=getRawRotation();
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
}
