/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:09/30/2019*/
/*************************************************************************/

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor{
  public:
    Motor(int ina[], int inb[], int pwm[], float tp, float tpalineacion);
    void setMotor(float a, float b, float c);
    void mov(int angle, int error); //En mov agrego los angulos
    //void alineacion(); //return kp para moverme
    void alineacionxd(float error);
    void test();
  private:
    int _ina[3];
    int _inb[3];
    int _pwm[3];
    int _anglewheel[3]={30,-30,90};
    float _tp;
    int _angle;
    int _error;
    int _tpalineacion;
    float _a;
    float _b;
    float _c;
};

#endif
