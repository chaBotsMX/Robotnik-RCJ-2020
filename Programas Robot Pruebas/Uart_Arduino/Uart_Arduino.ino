int angulo;
void setup() {
  Serial.begin(19200);
  Serial3.begin(19200);
}

void loop() {
  if (Serial3.available() > 0) {
    angulo = Serial3.read();
    Serial.println(angulo);
  }
}
