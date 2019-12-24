#include <iostream>
#include <math.h>

using namespace std;
/*
    PID Chabots Robotnik Prueba en C++
*/


int main(){
    int a=80;
    int b=20;

    int C=160;
    //((a*a)+(b*b))-2(a)*(b)*cos(C))
    while(a!=b&&C!=0){
    double c= sqrt(((a*a)+(b*b))-2*(a*b)*cos(C*M_PI/180.00));
    double x=((a*sin(C*M_PI/180.00))/c);
    double d = asin(x)*180.00/M_PI;
    b=b+50;
    C=C-5;
    cout<<180.00-C-d<<"\t"<<d<<"\t"<<180-(180.00-C-d)<<"\n";
    }
}
