
int redLed = 10;
int greenLed = 11;
int buzzer = 12;
int smokeA0 = A0;
// Your threshold value
int sensorThres = 400;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}

void loop() {
  int analogSensor = analogRead(smokeA0);

  Serial.print("Pin A0: ");
  Serial.println(analogSensor);
  // Checks if it has reached the threshold value
  if (analogSensor >= sensorThres)
  {
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    digitalWrite(redLed, HIGH);
    delay(100);
    digitalWrite(redLed, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    
  }
  else
  {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed,LOW);
    digitalWrite(buzzer, LOW);
    
  }
  delay(100);
}
