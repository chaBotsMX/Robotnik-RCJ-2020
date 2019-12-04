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
    Motor(int ina[], int inb[], int pwm[], float tp, int tpalineacion);
    void set(float a, byte n);
    void move(int angle, float error);
    void alineacion(float error);
    //void alineacion(); //return kp para moverme
    /*void alineacionxd(float error);
    void test();*/
  private:
    int _ina[4];
    int _inb[4];
    int _pwm[4];
    int anglewheel[4]={0,30,-30,90};
    float _tp;
    int _tpalineacion;
};

#endif
