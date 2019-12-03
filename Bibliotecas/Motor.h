/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Lib Control V 1.0														 */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:09/30/2019*/
/*************************************************************************/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(int _ina[], int _inb[], int _pwm[], float _tp, float _tpalineacion);
    void setMotor(float a, float b, float c);
    void mov(int angle, int error); //En mov agrego los angulos
    //void alineacion(); //return kp para moverme
    void alineacionxd(float error);
    void test();
  private:
    int ina[4];
    int inb[4];
    int pwm[4];
    int anglewheel[3]={30,-30,90};
    float tp;
    int tpalineacion;
};

#endif
