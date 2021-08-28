/*
  Open MenuAutomatic Lights Using LDR (Brightness Control)

*/

int LED = 9; // attached to pin for pwm output
int LDR = A7; // LDR attached to analog7 [A7]
int value = 0; // varible to store ldr data

void setup()
{

  Serial.begin(9600);
}
void loop()
{
  value = analogRead(LDR);
  Serial.print("LDR input ");
  Serial.print(value);

  value = constrain(value, 0, 260);
  value = map(value, 0, 260, 255, 0); //

  Serial.print(" , LED output ");
  Serial.println(value);

  analogWrite(LED, value);

  delay(200);
}
