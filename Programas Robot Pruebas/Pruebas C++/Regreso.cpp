#include <iostream>
using namespace std;

/*
    Chabots Robotnik Regreso a zona defenza
*/
int main(){
    int us1=100;    //ATRAS
    int us2=50;     //DERECHA
    int us3=80;     //IZQUIERDA

    bool lado = us1>us2 ? 1 : 0;
    us2=91-50;     //DERECHA
    us3=91-80;     //IZQUIERDA

    cout<<lado;
}
