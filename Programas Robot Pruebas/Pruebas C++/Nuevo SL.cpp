#include <iostream>
#include <math.h>
using namespace std;
            // 0 90 180 270
int sensorX[]={1,0,-1,0};
int sensorY[]={0,1,0,-1};
int mov[]={180,270,360,90};
bool sensor[3];
int contador=0;
/*
    Procesar mientras esta en linea
*/
int main(){
    int angle=0;
    int sumax=0;
    int sumay=0;
    int suma=0;
    int contador=0;
    bool S1,S2,S3,S4;
    cin>>sensor[0]>>sensor[1]>>sensor[2]>>sensor[3];
    for(int i=0; i<=3; i++){

        if(sensor[i]){
            contador > 1 ? sensor[2] = 0 : sensor[2] = 360;
            suma=suma+mov[i];
            contador++;
        }
    }

    angle=(suma/contador)%360;
    cout<<angle;
}
