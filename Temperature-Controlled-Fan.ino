/* Temperature Controlled Fan using Arduino

*/

float temp ; // varible for sensor

int Fan = 9; // fan attached to pin 9 [PWM]

int val ; // to store the rpm data for fan

int led2 = 2;
int led3 = 3;
int led4 = 4;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //Defining Led pins as output

  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);



}

void loop() {
  // put your main code here, to run repeatedly:

  temp = analogRead(A0); // Read Pin A0 for temperature
  temp = temp * 0.48828122 ;// multiply temp redings by constant factor to get readings in celcius


  // For debuging

  Serial.print(" temperature ");
  Serial.print(temp);
  Serial.print(" *C");


  val = temp ;          // reads the value of the temperature
  val = map(val, 0, 45, 0, 255);     // scale it for use with fan (value between 0 and 255)

  Serial.print(" , FanSpeed  ");
  Serial.print(val);
  Serial.println(" PWM");

  analogWrite(Fan, val);                 // sets the fan speed according to the scaled value



  if (temp > 25) {

    digitalWrite(led2, HIGH);
    delay(500);

  }
  if (temp > 35) {

    digitalWrite(led3, HIGH);
    delay(500);

  }
  if (temp > 44) {

    digitalWrite(led4, HIGH);
    delay(500);

  } else {

    analogWrite(Fan, 0);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}
