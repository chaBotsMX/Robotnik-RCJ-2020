/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Lib Control V 1.0														 */	
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:09/30/2019*/
/*************************************************************************/

#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int ina[], int inb[], int pwm[], float tp, int tpalineacion){
    for(int i=0; i<3; i++){
      pinMode(ina[i],OUTPUT);
      pinMode(inb[i],OUTPUT);
      pinMode(pwm[i],OUTPUT);
    }
    _tp=tp;
    _tpalineacion=tpalineacion;
}

void mov(int angle, int error){
  error = _error;
  angle = _angle;
  float a=cos((angle-30)*M_PI/180)*tp;
  float b=cos((angle+30)*M_PI/180)*tp;
  float c=-cos((angle-90)*M_PI/180)*tp;
  float kp=(_error/180*tp);
  //Motor A
  setMotor(a-kp, b+kp,c-kp);
}

void setMotor(float a, float b, float c){
	if(a>=0){//adelant
		a=abs(a);
		a=min(a,tp);
		//adelante
		digitalWrite(24,LOW);
		digitalWrite(25,HIGH);
		analogWrite(7,b);
		digitalWrite(13,LOW);
	}
	else if(a<0){ //atras
		a=abs(a);
		a=min(a,tp);
		digitalWrite(24,HIGH);
		digitalWrite(25,LOW);
		analogWrite(7,b);
		digitalWrite(13,LOW);
	}
	if(b>=0){//adelante
		b=abs(b);
		b=min(b,tp);
		digitalWrite(52,LOW);
		digitalWrite(53,HIGH);
		analogWrite(8,a);
		digitalWrite(13,LOW);
	}
	else if(b<0){ //atras
		b=abs(b);
		b=min(b,tp);
		digitalWrite(52,HIGH);
		digitalWrite(53,LOW);
		analogWrite(8,a);
		digitalWrite(13,LOW);
	}
	if(c>=0){//adelante
		c=abs(c);
		c=min(c,tp);
		digitalWrite(23,LOW);
		digitalWrite(22,HIGH);
		analogWrite(2,c);
		digitalWrite(13,LOW);
	}
	else if(c<0){ //atras
		c=abs(c);
		c=min(c,tp);
		digitalWrite(22,LOW);
		digitalWrite(23,HIGH);
		analogWrite(2,c);
		digitalWrite(13,LOW);
	}
}

void alineacionxd(){
  digitalWrite(13,HIGH);
}

void test(){
  digitalWrite(13,HIGH);
}
