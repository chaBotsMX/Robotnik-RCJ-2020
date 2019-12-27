int lectura,lectura2,lectura3;
void setup() {
  Serial.begin(115200);
  lectura=0;
  lectura2=0;
  lectura3=0;
}
int a;  
int b;
int contador=0;
long long int tiempo;

void loop() {
  
  lectura=max(lectura,analogRead(A1));
  
  lectura2=max(lectura2,analogRead(A2));
  lectura3=max(lectura3,analogRead(A3));
  
  if(micros()-tiempo>15000){
    tiempo=micros();
     /* 
    if(lectura>10){
      lectura=1;    
      contador++;m
    }
    //Serial.println(lectura>10);
    /*if(lectura==1){
      contador++;
    }
    if(contador>=8)
      Serial.println(1);
      else
      Serial.println(0);
      */
    
      Serial.print(lectura);
    Serial.print("\t");
      Serial.print(lectura2);
    Serial.print("\t");
    
      Serial.print(lectura3);
    Serial.print("\t");
    Serial.print("\n");
     lectura=0;
     lectura2=0; 
     lectura3=0; 
  }
}
