/* Temperature Controlled Fan using Arduino

*/

int  temp ; // varible for sensor

int Fan = 9; // fan attached to pin 9 [PWM]

int val ; // to store the rpm data for fan

int rpm = 0 ;

int led2 = 2;
int led3 = 3;
int led4 = 4;

//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display



void setup() {


  Serial.begin(9600);

  lcd.init();                      // initialize the lcd
  lcd.init();

  // Print a message to the LCD.

  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Controlled-Fan");

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



  rpm = val * 9.25; // constant for rpm
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Temperature ");
  lcd.setCursor(12, 0);
  lcd.print(temp);
  lcd.setCursor(14, 0);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  lcd.print("RPM :");
  lcd.setCursor(6, 1);
  lcd.print(rpm);



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

    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}
