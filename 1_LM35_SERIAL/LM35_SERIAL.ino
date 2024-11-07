float tempC;
int reading;
int tempPin = 0;

void setup() {
  analogReference(INTERNAL);
  Serial.begin(9600);
}

void loop() {
  reading = analogRead(tempPin);
  tempC = reading / 9.31;
  Serial.print(tempC);
  Serial.println(" C");
  delay(1000);
}
