#include <iostream>
#include <math.h>

using namespace std;
/*
    PID Chabots Robotnik Prueba en C++
*/


int main(){
    int a=80;
    int b=20;
    bool x;
    int C=10;
    C>180 ? x=1 : x=0;
    C>180 ? C=360.00-C : C=C;

    //((a*a)+(b*b))-2(a)*(b)*cos(C))
    while(a!=b&&C>0){
        double c= sqrt(((a*a)+(b*b))-2*(a*b)*cos(C*M_PI/180.00));
        double d = asin(((a*sin(C*M_PI/180.00))/c))*180.00/M_PI;
        b=b+1;
        C=C-5;
        if(!x)
            cout<<180.00-C-d<<"\t"<<d<<"\t"<<180-(180.00-C-d)<<"\n";
        else
            cout<<180.00-C-d<<"\t"<<d<<"\t"<<180+(180.00-C-d)<<"\n";
    }
    cout<<a<<"\t"<<b<<"\t"<<C;
}
