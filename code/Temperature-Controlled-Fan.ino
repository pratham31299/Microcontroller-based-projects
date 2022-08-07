/* Temperature Controlled Fan using Arduino

*/

//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// GPIO pins

#define Fan 9 // fan attached to GPIO pin 9 (PWM)
/*
  #define led2 2 // led pins
  #define led3 3
  #define led4 4
*/
#define tempPin A3 // LM35 is connected to this PIN


// Variables
int val = 0;
int temp = 0; // varible for sensor
int pwm_Value  = 0; //
int fan_Speed = 0 ;



void setup() {


  Serial.begin(9600); // at 9600 baud rate

  // Initialize the lcd
  lcd.init();
  lcd.init();

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Temperature");
  lcd.setCursor(0, 1);
  lcd.print("Controlled-Fan");

  pinMode(Fan, OUTPUT);
  pinMode(tempPin, INPUT);

  /*
    //Defining Led pins as output

    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
  */


}

void loop() {

  val = analogRead(tempPin); // Read Pin A0 for temperature

  // Convert that ADC Data into voltage (5.0 / 1024.0),  Convert the voltage into temperature (* 100)
  temp = val * 0.48828122 ;// multiply temp redings by constant factor to get readings in celcius


  pwm_Value = map(temp, 20, 40, 0, 255);     // scale it for use with fan (value between 0 and 255), max speed at 40*C
                                             // min speed at 20*C
  if (temp > 40 ) { // map function exception

    pwm_Value = 255 ; // max speed
  }


  analogWrite(Fan,  pwm_Value);  // sets the fan speed according to the scaled value

  fan_Speed = map(pwm_Value, 0, 255, 0, 100);    // to display fan speed ( 0 - 100% )corresponding to pwm output


  // LCD show

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  lcd.print(temp);
  lcd.setCursor(9, 0);
  lcd.print("*C");
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.setCursor(7, 1);
  lcd.print(fan_Speed);
  lcd.setCursor(10, 1);
  lcd.print("%");

  /*

    // Led control structure

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

  */

  // for debugging
  Serial.print("Temp analog read : ");
  Serial.print(val);
  Serial.print(" ,Temp : ");
  Serial.print(temp);
  Serial.print(" *C");
  Serial.print(" , PWM : ");
  Serial.print(pwm_Value);
  Serial.print(" , Fan Speed ");
  Serial.print(fan_Speed);
  Serial.println(" %");

  delay(200);
}
