void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(44,OUTPUT);
  pinMode(52,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(52)){
    Serial.println("1");
    digitalWrite(44,LOW);
    delay(100);
  }
  else
    digitalWrite(44,HIGH);
}
