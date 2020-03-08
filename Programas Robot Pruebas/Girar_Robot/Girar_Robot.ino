#include <Wire.h>
#include <DueFlashStorage.h>
#include "IRLocator360.h"
#include "UltrasonicoLib.h"
#include "Motor.h"
#include "SparkFun_BNO080_Arduino_Library.h"
#define in 140
#define inn 19600
//3537
int ina[]={0,36,40,49};
int inb[]={0,38,42,23};
int pwm[]={0,13,12,2};  
int vel=125;

const int magx = -99;
const int magy = -134;

Motor mot(ina,inb,pwm,255,255);
IRLocator360 IR;
DueFlashStorage dueFlashStorage;
Ultrasonico us2(6,5);
double targetRotation=0.0;
double Set=0.0;
BNO080 myIMU;

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
  return atan2(x-magx, y-magy)*180.00/M_PI;
}

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

double escribir(int alineacion){
  dueFlashStorage.write(3, alineacion%255);
  dueFlashStorage.write(4, alineacion/255);
  delay(50);
}

double magn;
bool im;
int camara=0;
void setup() {
  Serial.begin(19200);  
  Serial3.begin(19200);
  Wire.begin();
  myIMU.begin();
  myIMU.enableRotationVector(50);
  myIMU.enableMagnetometer(50);
  targetRotation=dueFlashStorage.read(3)+dueFlashStorage.read(4)*255;
  while(millis()<600){
    Set=getRawRotation()+(targetRotation-mag());
    delay(20);
  }  
  IR.sensorInitialization();
  pinMode(9,OUTPUT);
  pinMode(8,INPUT_PULLUP);
  delay(20);
}

float alin=180.00;
int vela=255;
float a,b,c;

void loop() {
  if (Serial3.available() > 0) {
    camara = Serial3.read();
    camara=camara-120; 
    Serial.println(camara);
  }
  int intensidad=IR.signalStrength1200hz();
  int angle=IR.angleDirection600hz();  
  bool x;
  
  double erro = getRawRotation() - Set;
  
  erro < 0 ? erro= 360.00+erro : erro=erro;  
  
  double imu=error(erro);
  
    /*imu=imu+10;
    vela=200;
    angle=0;*/
  mot.alineacion(imu);  
  if(imu>=-5&&imu<=5)
    digitalWrite(9,HIGH);
  else
    digitalWrite(9,LOW);

  if(!digitalRead(8)==1){
    magn=mag();
    magn > 0 ? magn=magn : magn=360.00+magn;
    escribir(magn);
    Set=getRawRotation();
    mot.off();
  }  
  
  delay(20);
}
