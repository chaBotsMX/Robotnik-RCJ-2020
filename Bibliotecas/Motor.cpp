/*************************************************************************/
/*                                                                           */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Lib Control V 1.0														 */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:09/30/2019*/
/*************************************************************************/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int _ina[], int _inb[], int _pwm[], float _tp, int _tpalineacion){
    for(int i=1; i<=3; i++){
      ina[i]=_ina[i];
      inb[i]=_inb[i];
      pwm[i]=_pwm[i];
      pinMode(ina[i],OUTPUT);
      pinMode(inb[i],OUTPUT);
      pinMode(pwm[i],OUTPUT);
    }
    tp=_tp;
    tpalineacion=_tpalineacion;
}

void Motor::setMotor(float a, float b, float c){
  bool dir=0;
  dir= a>0? 1:0;
  digitalWrite(ina[1], dir);
  digitalWrite(inb[1], !dir);
  dir= b>0? 1:0;
  digitalWrite(ina[2], dir);
  digitalWrite(inb[2], !dir);
  dir= c>0? 1:0;
  digitalWrite(ina[3], dir);
  digitalWrite(inb[3], !dir);
}

void Motor::mov(int angle, int error){

  float a=cos((angle-30)*M_PI/180)*tp;
  float b=cos((angle+30)*M_PI/180)*tp;
  float c=-cos((angle-90)*M_PI/180)*tp;
  float kp=(error/180*tp);
  //Motor A
  setMotor(a-kp, b+kp,c-kp);

}

void Motor::alineacionxd(){
  digitalWrite(13,HIGH);
}

void Motor::test(){
  digitalWrite(13,HIGH);
}
