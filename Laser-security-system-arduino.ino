int buz = 2;
int LDR = A7; // LDR attached to analog7 [A7]

int value = 0; // varible to store ldr data

void setup() {
  // put your setup code here, to run once:
  pinMode(buz, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  value = analogRead(LDR);
  Serial.print("LDR input ");
  Serial.println(value);

  value = constrain(value, 0, 260);
  value = map(value, 0, 260, 255, 0); //
  if (value >= 200) {

    digitalWrite(buz, HIGH);

  } else {
    digitalWrite(buz, LOW);
  }


}
