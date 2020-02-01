#include <iostream>
#include <math.h>
using namespace std;
/*
    PID Chabots Robotnik Prueba en C++
*/


int main(){
    int a=80; //Intencidad actual de la pelota
    int b=20; // Intensidad constante de la pelota
    bool x; // Bandera
    int C=225; // Angulo actual del sensor IR
    C>180 ? x=1 : x=0; //Bandera
    C>180 ? C=360.00-C : C=C; // Mayor o menor a 180
    while(a!=b&&C!=180){
    //((a*a)+(b*b))-2(a)*(b)*cos(C))
        double c= sqrt(((a*a)+(b*b))-2*(a*b)*cos(C*M_PI/180.00));  //Calculo del lado del angulo IR
        double d = asin(((a*sin(C*M_PI/180.00))/c))*180.00/M_PI; //Calculo de angulo restante
        b=b+1;
        C=C+5;
        if(!x)
            cout<<(180-d)<<"\n";
        else
            cout<<180+d<<"\n";
    }

}
