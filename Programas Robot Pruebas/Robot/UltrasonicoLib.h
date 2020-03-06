struct Ultrasonico{
  private:
    byte port[2];

  public:
    void PAU(){
      pinMode(port[1], INPUT);
      pinMode(port[0], OUTPUT);
      digitalWrite(port[1], LOW);//Inicializamos el pin con 0
    }
    int VCM(){
      const int Trigger = port[0];   //Pin digital 2 para el Trigger del sensor
      const int Echo = port[1];   //Pin digital 3 para el Echo del sensor
      long t; //timepo que demora en llegar el eco
      long d; //distancia en centimetros
      digitalWrite(Trigger, HIGH);
      delayMicroseconds(10);          //Enviamos un pulso de 10us
      digitalWrite(Trigger, LOW);
      t = pulseIn(Echo, HIGH); //obtenemos el ancho del pulso
      d = t/59;             //escalamos el tiempo a una distancia en cm
      return d;
    }

  Ultrasonico(byte port1, byte port2){
    port[0]=port1;
    port[1]=port2;
  }
};
