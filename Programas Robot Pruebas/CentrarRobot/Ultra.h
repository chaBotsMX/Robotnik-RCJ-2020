/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Lib Ultrasonico V1.0														                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:01/08/2020*/
/*************************************************************************/

#ifndef Ultra_h
#define Ultra_h

#include "Arduino.h"

class Ultra
{
  public:
    //Trigger Echo
    Ultra(int trig, int echo);
    int cm();
  private:
    int _trig;
    int _echo;
};

#endif
