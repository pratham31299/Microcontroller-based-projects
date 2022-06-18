
#include <Servo.h> // servo library
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define trigPin 4 // digital GPIO
#define echoPin 5
#define trigPin1 6
#define echoPin1 9

long duration;
int distance, Meas_distance,  Meas_distance1;

Servo my_servo; // servo instance
SoftwareSerial SIM800_serial(3, 2 ); //Create software serial object to communicate with SIM800 (TX, RX)
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


int Cal_distance(int TRIG ,  int ECHO ) {  // function to calculate distance, with arrguments

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH);

  distance = duration * 0.034 / 2; // formula
  return distance ; // return distance value

}



void send_SMS() {

  delay(1000);
  SIM800_serial.println("AT"); // software serial
  delay(1000);
  SIM800_serial.println("AT+CMGF=1");          // Configuration for sending SMS
  delay(1000);
  SIM800_serial.println("AT+CMGS=\"+91748XXXXXXX\"\r");
  delay(500);
  SIM800_serial.print("SMS Alert ! Dustbin full");
  delay(1000);
  SIM800_serial.write(26);
  delay(1000);

  // print message
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.println("SMS sent       ");
  Serial.println("SMS sent");
  delay(3000);

}



void setup() {

  // initialize the lcd

  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Initializing....");

  Serial.begin(9600);  //Serial COM for debugging
  SIM800_serial.begin(9600); // software serial

  Serial.println("Initializing....");

  pinMode(trigPin, OUTPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(echoPin1, INPUT);
  my_servo.attach(10); // digital pin 10  (PWM)
  my_servo.write(0); // initial position

  // Print a message to the LCD.
  delay(5000);
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Smart Dustbin");
  delay(10000); // 10 sec

  Serial.println("System started ");
  Serial.println("");

}


void loop() {

  Meas_distance =  Cal_distance(trigPin, echoPin); // call function
  delay(1000);

  Meas_distance1 =  Cal_distance(trigPin1, echoPin1); // call function


  // Controle Structure---------------------------------------------------------------------------------------




  if ( Meas_distance < 20) { // 20   cm

    Serial.println("HOLD ON");
    my_servo.write(95); // Open dustbin lid
    delay(5000);

  } else {

    my_servo.write(0);
    Serial.print("Ultrasonic 0 : ");
    Serial.print(Meas_distance);

  }

  if ( Meas_distance1 < 10) { // 10 cm, dustbin full

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Dustbin Full !! ");
    lcd.setCursor(0, 1);
    lcd.println("Sending SMS...   ");
    delay(10000);

    Serial.println("Dustbin full !");
    Serial.println("Sending SMS...");
    send_SMS();

  } else {

    Serial.print(" Ultrasonic 1 : ");
    Serial.print(Meas_distance1);
    Serial.println(" cm");
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("USE ME '_'");  // Always show USE ME label
  }



  delay(1000); // a bit of delay
}
