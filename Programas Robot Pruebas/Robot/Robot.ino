#include "SparkFun_BNO080_Arduino_Library.h"
#include <Wire.h>
#include <DueFlashStorage.h>
#include "IRLocator360.h"
#include "Motor.h"
#define in 120
#define inn 14400
//3537
int ina[]={0,3,35,30};
int inb[]={0,14,37,32};
int pwm[]={0,8,7,6};

const int magx = 10;
const int magy = 5;

Motor mot(ina,inb,pwm,230,230);
IRLocator360 IR;
DueFlashStorage dueFlashStorage;

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
}


void setup() {
  Serial.begin(9600);  
  Wire.begin();
  
  myIMU.begin();
  myIMU.enableRotationVector(50);
  myIMU.enableMagnetometer(50);
  targetRotation=dueFlashStorage.read(0)+dueFlashStorage.read(1);
  Set=getRawRotation()+(targetRotation-getRotation());
  
  IR.sensorInitialization();
  pinMode(9,OUTPUT);
  pinMode(52,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
 //7 pinMode(5,OUTPUT);
}

void loop() {
  int intensidad=IR.signalStrength1200hz();
  int angle=IR.angleDirection600hz();  
  bool x;
  /*if(angle>=10||angle<=180)
    angle=angle+10;
  else if(angle>180||angle<=350)
    angle=angle-10;*/
  double erro = getRawRotation() - Set;
  
  erro < 0 ? erro= 360.00+erro : erro=erro;  
  
  double imu=error(erro);
  
  if(angle<=355&&angle>=5){
  angle>=180 ? x=1 : x=0; 
  angle>=180 ? angle=360.00-angle : angle=angle;
  double t=sqrt(((intensidad*intensidad)+(inn))-2*(intensidad*in)*cos(angle*M_PI/180.00));
  double d=asin(((intensidad*sin(angle*M_PI/180.00))/t))*180.00/M_PI;
  if(!x)
    angle=180.00-(180.00-angle-d);
  else
    angle=180.00+(180.00-angle-d);
  }
  
  //Serial.println(error(getRotation()));
  //Serial.println(getFilter(360.00-getRotation()));
  //Serial.println(erro);
  
  if(abs(imu)>=175||abs(imu)<=5)
    digitalWrite(9,HIGH);
  else
    digitalWrite(9,LOW);
    
  float valor=(imu/180.00*255);
  
  float a=cos((angle-(30))*M_PI/180)*150;
  float b=cos((angle+30)*M_PI/180)*150;
  float c=-cos((angle-90)*M_PI/180)*150;    
    
  mot.set(valor+a,1);
  mot.set(valor+b,2);
  mot.set(valor-c,3);
  
 
  
  //mot.alineacion(erro);  
//  float valor=(erro/180.00*200);
  //for(int i=1; i<=3; i++)
    //mot.set(valor, i);
  Serial.println(imu);
   
  if(!digitalRead(52)==1){
    escribir(mag());
    Set=getRawRotation();
  }
  if(!digitalRead(2)==1){
    myIMU.softReset();  
  }
}
