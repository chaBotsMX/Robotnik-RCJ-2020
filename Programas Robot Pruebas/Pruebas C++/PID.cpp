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
    int C=0; // Angulo actual del sensor IR
    C>180 ? x=1 : x=0; //Bandera
    C>180 ? C=360.00-C : C=C; // Mayor o menor a 180

    //((a*a)+(b*b))-2(a)*(b)*cos(C))
    while(a!=b&&C>0){
        double c= sqrt(((a*a)+(b*b))-2*(a*b)*cos(C*M_PI/180.00));  //Calculo del lado del angulo IR
        double d = asin(((a*sin(C*M_PI/180.00))/c))*180.00/M_PI; //Calculo de angulo restante
        b=b+1;
        C=C-5;
        if(!x) // Un angulo         Otro angulo         A donde se va a mover
            cout<<180.00-C-d<<"\t"<<d<<"\t"<<180-(180.00-C-d)<<"\n";
        else
            cout<<180.00-C-d<<"\t"<<d<<"\t"<<180+(180.00-C-d)<<"\n";
    }
    cout<<a<<"\t"<<b<<"\t"<<C;
}
