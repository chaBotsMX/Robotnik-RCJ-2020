long readLimit;
long timeLimit=833;
int count=0;
void setup() {
  Serial.begin(115200);
  pinMode(7,INPUT);
  pinMode(13,OUTPUT);
  readLimit=millis()+50;
}

int lectura(){
  const unsigned long startTime_us = micros();
    do {
            if(!digitalRead(7) ) {
                count++;
            }
        
    } while((micros() - startTime_us) < timeLimit);
  return count;
}

void loop() {
  if(millis()>readLimit){
    Serial.println(lectura());
    count=0;
  }
}
