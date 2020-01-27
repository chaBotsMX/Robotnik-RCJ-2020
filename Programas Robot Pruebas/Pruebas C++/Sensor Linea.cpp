#include <iostream>
#include <math.h>
using namespace std;
            // 0 90 180 270
int sensorX[]={1,0,-1,0};
int sensorY[]={0,1,0,-1};
int mov[]={180,270,0,90};
bool sensor[3];
int contador=0;
/*
    Procesar mientras esta en linea
*/
int main(){
    int angle=0;
    int sumax=0;
    int sumay=0;
    bool S1,S2,S3,S4;
    cin>>sensor[0]>>sensor[1]>>sensor[2]>>sensor[3];
    sensor[0]>0 ?  sumax = sumax + sensorX[0] : sumay= sumay + sensorY[0]; // 0
    sensor[1]>0 ?  sumay = sumay + sensorY[1] : sumax= sumax + sensorX[1]; // 90
    sensor[2]>0 ?  sumax = sumax + sensorX[2] : sumay= sumay + sensorY[2]; // 180
    sensor[3]>0 ?  sumay = sumay + sensorY[3] : sumax= sumax + sensorX[3]; // 270
    if(sumax!=0&&sumay!=0){
        angle=atan((sumay/sumax))*180.00/M_PI;
        if(angle<0){
            if(sensor[1])
                angle=angle+360;
            else
                angle=angle+180;
        }
        else
           angle=angle+180;
    }
    else{
        if(sumax==0&&sumay==0)
            angle=180;
        else
            for(int i=0; i<=3; i++){
                if(sensor[i]){
                    angle=angle+mov[i];
                    contador++;
                }
            }
    }
    if(contador==3){
        if(angle==360||angle==540)
            angle=angle-360;
        else
                angle=angle-180;
    }
    cout<<angle;
}
