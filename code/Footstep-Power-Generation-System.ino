
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

float vanalog = A0; // voltage divider on analog pin A0

float vout = 0.0;
float vin = 0.0;
float R1 = 100000.0 ; // R1 [100k]
float R2 = 10000.0  ;// R2 [10k]

int value = 0;

int count = 0; // to count footstep



void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  pinMode(vanalog, INPUT);
  lcd.setCursor(1, 0);
  lcd.print("FootStep Power");
  lcd.setCursor(0, 1);
  lcd.print("GenerationSystem");
  delay(5000);
  lcd.clear();


}


void loop()
{

  // Calculation

  value = analogRead(vanalog); // analog read to get data form Input [ 0 v = 0 , 5 v = 1023]

  vout = (value * 5.0 ) / 1024.0 ; // Converting it into voltage Respectively

  vin = (vout / (R2 / R1 + R2) ); //voltage divider formula

  //Print data on LCD

  lcd.setCursor(0, 1);
  lcd.print("Voltage ");
  lcd.setCursor(9, 1);
  lcd.print( value);

  if ( vin > 0.5) { // minimum  voltage which can be detected

    count++; // for footstep incriment by 1
    lcd.setCursor(0, 0);
    lcd.print("FootStep ");
    lcd.setCursor(9, 0);
    lcd.print(count);
    delay(1000);
  }

}