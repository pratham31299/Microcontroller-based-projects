/*

  july 10 2022

*/

#include "math.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


//******************************IoT Blynk****************************

#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_DEVICE_NAME "Device name"
#define BLYNK_AUTH_TOKEN "Your auth token"  // auth token

#define BLYNK_PRINT Serial // Comment this out to disable prints and save space

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>


//WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID"; // set network SSID, "My SSID"
char pass[] = "password";  // set network Password,  "My Password"

char auth[] = "Your auth token";



// Input GPIO pins
#define mq7_Pin 35 // select the analog input pin for sensor MQ-7
#define temp_Pin 34    // select the analog input pin for sensor LM35
#define mq2_Pin 32 // select the analog input pin for sensor MQ-2


//Output GPIO pins
#define buzzer 2 // pin 2


// Variables

int SMS_count = 0; // to count no. SMS's

// Store the value coming from the sensor
int temp_Value = 0;
int mq2_Value = 0;
int mq7_Value = 0;

//Set safety threshold levels for hazardous gas and temperature
const int  CH4_thresh = 1000;  //Methane level
const int CO_thresh = 50;  // Carbon monoxide
const int Temp_thresh = 50; // temperature in °C

// Store final value
double CO_ppm = 0 ;
double CH4_ppm = 0 ;
float temp = 0;



void send_SMS() {  // function to send SMS alert via SIM900A module

  Serial.println("Sending Message....");
  delay(1000);
  Serial2.println("AT"); //AT commands -> OK
  delay(500);
  Serial2.println("AT+CMGF=1");    // Configuring TEXT mode
  delay(500);
  Serial2.println("AT+CMGS=\"+9162XXXXXXXX\"");   //sms receiving phone number
  delay(500);
  Serial2.println("Emergency ! Alert "); //text content
  Serial2.println("Evacuate Mine");
  Serial2.println("");
  Serial2.print("Methane (CH4): ");  // send gases level
  Serial2.print(CH4_ppm);
  Serial2.println(" ppm");
  Serial2.print("Carbon Monoxide (CO): ");
  Serial2.print(CO_ppm );
  Serial2.println(" ppm");
  Serial2.print("Temperature: ");  // send temperature level
  Serial2.print(temp);
  Serial2.println(" C");
  delay(500);
  Serial.println();
  Serial.println("Message Sent");
  Serial2.write(26);
  delay(2000);
}




void setup() {

  // Initlize debugging console
  Serial.begin(9600); // at 9600 baud rate

  Serial2.begin(9600); // SIM900A module serial
  delay(3000);


  // Initilize IoT Blynk
  WiFi.begin();
  Blynk.begin(auth, ssid, pass);

  lcd.init();  // Initialize the lcd
  lcd.backlight();

  // initialize digital pin buzzer as an output.
  pinMode(buzzer, OUTPUT);

  // Print a message to the LCD.

  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(5000);
  lcd.clear();
  lcd.print("Coal mine safety");
  lcd.setCursor(0, 1);
  lcd.print("monitoring and ");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("alerting system!");
  delay(3000);

}



void loop() {

  // read the value from the sensor:-------------------------------

  temp_Value = analogRead(temp_Pin);
  mq2_Value = analogRead(mq2_Pin);
  mq7_Value = analogRead(mq7_Pin);

  //to get readings in celcius

  // convert the ADC value to voltage in millivolt
  temp = temp_Value  * (5000.0 / 4095.0); //ADC VREF mV  5000.0 in millivolt / ADC RESOLUTION 4096.0
  temp = temp / 10; // convert the voltage to the temperature in °C
  temp =  round(temp); // round off, stable floating value




  // to get gas readings in ppm------------------------------------------

  //https://learn.sparkfun.com/tutorials/hazardous-gas-monitor#calculate-gas-sensor-ppm

  CO_ppm = 3.027 * exp(1.0698 * (mq7_Value * 3.3 / 4095)); //Multiply raw analog value by 3.3/4095 to convert to a voltage

  CH4_ppm = 10.938 * 10.938 * exp(1.7742 * (mq2_Value * 3.3 / 4095));

  CO_ppm =  round(CO_ppm); // round off, stable floating value

  CH4_ppm =  round(CH4_ppm);




  // Data stream for debugging console----------------------------------

  Serial.print("Raw LM35: ");
  Serial.print(temp_Value);
  Serial.print(" Temp: ");
  Serial.print(temp);

  Serial.print(", Raw MQ-2: ");
  Serial.print(mq2_Value);
  Serial.print(" PPM: ");
  Serial.print(CH4_ppm);

  Serial.print(", Raw MQ-7: ");
  Serial.print(mq7_Value);
  Serial.print(" PPM: ");
  Serial.println(CO_ppm);


  // Send Data to IoT app (Blynk)---------------------------------------

  Blynk.virtualWrite(V0, temp );// display temperature on datastream Virtual pin V0
  Blynk.virtualWrite(V1, CH4_ppm);// display CH4 on Virtual pin V1
  Blynk.virtualWrite(V2, CO_ppm);// display CO on Virtual pin V2




  // Controle structure--------------------------------------

  if (temp > Temp_thresh || CH4_ppm >  CH4_thresh || CO_ppm >  CO_thresh) {  // If temperature any parameter cross the threshold values

    digitalWrite(buzzer, HIGH);// buzzer alert
    delay(1000);
    digitalWrite(buzzer, LOW);

    // show on LCD
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("WARNING !");
    delay(1000);

    if (SMS_count == 0) {  // if no SMS sent before, send SMS

      send_SMS();  // call SMS function
      SMS_count = 1; // count as 1

    }

  }


  // show on LCD------------------------------------

  //Temperature level (deg C)
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.setCursor(3, 0);
  lcd.print(temp);

  //Carbon Monoxide level (CO)
  lcd.setCursor(9, 0);
  lcd.print("CO:");
  lcd.setCursor(12, 0);
  lcd.print(CO_ppm);

  //Methane level (CH4)
  lcd.setCursor(0, 1);
  lcd.print("CH4: ");
  lcd.setCursor(5, 1);
  lcd.print(CH4_ppm);


  Blynk.run();
  delay(1000); // delay a bit

}
