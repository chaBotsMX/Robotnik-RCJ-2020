/*************************************************************************/
/*                                                                       */
/*                                                                       */
/****************************CHABOTS ROBOTNIK*****************************/
/*                                                                       */
/*Lib Ultrasonico V1.0														                       */
/*S.L.P MEXICO                           TIME:10:37:40 PM DATE:01/08/2020*/
/*************************************************************************/

#include "Arduino.h"
#include "Ultra.h"

Ultra::Ultra(int trig, int echo){
  _trig=trig;
  _echo=echo;
  pinMode(echo, INPUT);
  pinMode(trig, OUTPUT);
  digitalWrite(echo, LOW);//Inicializamos el pin con 0
}

int Ultra::cm(){
    long t; //timepo que demora en llegar el eco
    long d; //distancia en centimetros
    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);          //Enviamos un pulso de 10us
    digitalWrite(_trig, LOW);
    t = pulseIn(_echo, HIGH); //obtenemos el ancho del pulso
    d = t/59;             //escalamos el tiempo a una distancia en cm
    return d;

}
