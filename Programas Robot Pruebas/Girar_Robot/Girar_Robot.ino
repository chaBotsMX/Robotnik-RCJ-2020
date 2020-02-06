#include <Wire.h>
#include <DueFlashStorage.h>
#include "IRLocator360.h"
#include "Motor.h"
#include "SparkFun_BNO080_Arduino_Library.h"
#define in 140
#define inn 19600
//3537
int ina[]={0,14,35,30};
int inb[]={0,3,37,32};
int pwm[]={0,8,7,6};  
int vel=125;

const int magx = -99;
const int magy = -134;

Motor mot(ina,inb,pwm,255,255);
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

double escribir(int alineacion){
  dueFlashStorage.write(3, alineacion%255);
  dueFlashStorage.write(4, alineacion/255);
  delay(50);
}

double magn;
bool im;
void setup() {
  Serial.begin(19200);  
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
  pinMode(5,OUTPUT);
  pinMode(52,INPUT_PULLUP);
  pinMode(2,INPUT_PULLUP);
  pinMode(13,INPUT_PULLUP);
  delay(20);
 //7 pinMode(5,OUTPUT);
}
float alin=180.00;
int vela=255;
float a,b,c;
void loop() {
  
  int intensidad=IR.signalStrength1200hz();
  int angle=IR.angleDirection600hz();  
  bool x;
  /*if(angle>=10||angle<=180)z
    angle=angle+10;
  else if(angle>180||angle<=350)
    angle=angle-10;*/
  double erro = getRawRotation() - Set;
  
  erro < 0 ? erro= 360.00+erro : erro=erro;  
  
  double imu=error(erro);
  Serial.print(angle);
  Serial.print("\t");

  
  if(angle>=340||angle<=10){
    
    imu=imu+40;
    vela=200;
    digitalWrite(5,LOW);
    angle=0;
       a=cos((angle-(30))*M_PI/180)*vel;
       b=cos((angle+30)*M_PI/180)*vel;
      c=-cos((angle-90)*M_PI/180)*vel;    

  }
  else{
    a=0;
    b=0;
    c=0;
    vela=255;
    digitalWrite(5,HIGH);
    Serial.println("ÄAAAAAAAAAAAAAAAA");
  }

  
    float valor=(imu/alin*vela);
  mot.set(valor-a,1);
  mot.set(valor+b,2);
  mot.set(valor-c,3);
  
  
  if(imu>=-5&&imu<=5)
    digitalWrite(9,HIGH);
  else
    digitalWrite(9,LOW);

  //mot.alineacion(erro);  
//  float valor=(erro/180.00*200);
  //for(int i=1; i<=3; i++)
    //mot.set(valor, i);
   Serial.print(vela);
  Serial.print("\t");
  Serial.print(angle);
  Serial.print("\t");
  Serial.println(imu);
   
  if(!digitalRead(52)==1){
    magn=mag();
    magn > 0 ? magn=magn : magn=360.00+magn;
    Serial.println(magn);
    escribir(magn);
    
    Set=getRawRotation();
    mot.off();
  }  
  if(!digitalRead(2)==1){
    myIMU.softReset();  
  }
  delay(20);
}
