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

Motor::Motor(int ina[], int inb[], int pwm[], float tp, int tpalineacion){
    for(int i=1; i<=3; i++){
        _ina[i]=ina[i];
        _inb[i]=inb[i];
        _pwm[i]=pwm[i];
        pinMode(ina[i],OUTPUT);
        pinMode(inb[i],OUTPUT);
        pinMode(pwm[i],OUTPUT);
    }
    _tp=tp;
    _tpalineacion=tpalineacion;
}

void Motor::set(float a, byte n){
    bool dir= a>0? 1:0;
    digitalWrite(_ina[n], dir);
    digitalWrite(_inb[n], !dir);
    analogWrite(_pwm[n], abs(a));
}

void Motor::move(int angle, double error){
    float valor=(error/180.00*_tpalineacion);
    for(int i=1; i<=3; i++){
        //float a=cos((angle+(anglewheel[i]))*M_PI/180)*_tp;
        float a = nop[i]>0 ? cos((angle+(anglewheel[i]))*M_PI/180)*_tp : -cos((angle+(anglewheel[i]))*M_PI/180)*_tp;
        set(valor+a,i);
    }
}

void Motor::alineacion(double error){

}
