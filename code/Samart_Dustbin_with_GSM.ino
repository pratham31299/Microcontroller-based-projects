
#include <Servo.h> // servo library
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#define trigPin 4 // digital GPIO
#define echoPin 5
#define trigPin1 6
#define echoPin1 9

long duration;
int distance, Meas_distance,  Meas_distance1;

int SMS_count = 0 ; // to count no. of sent SMS


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
  SIM800_serial.println("AT"); // software serial OK
  delay(1000);
  SIM800_serial.println("AT+CMGF=1");  // Configuration for sending SMS
  delay(1000);
  SIM800_serial.println("AT+CMGS=\"+9162XXXXXXXXX\"\r"); // SMS receiving number
  delay(500);
  SIM800_serial.print("SMS Alert ! Dustbin full"); // SMS 
  delay(1000);
  SIM800_serial.write(26);
  delay(1000);

  Serial.println("SMS sent");

  // LCD show
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.println("SMS sent       ");
  delay(3000);
  lcd.clear(); // LCD clear All

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
  delay(500);

  Meas_distance1 =  Cal_distance(trigPin1, echoPin1); // call function



  // Controle Structure------------------------------------------------------


  if ( Meas_distance < 20) { // 20 cm, dustbin use case

    Serial.println("HOLD ON");

    // LCD show
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("HOLD ON");

    // Open dustbin lid
    my_servo.write(95);
    delay(5000);  // delay

    // LCD show
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Thank You");
    delay(1500);

    // Dustbin closed
    my_servo.write(0);

  }


  if ( Meas_distance1 < 10) { // 10 cm, dustbin full

    Serial.println("Dustbin full !");

    // LCD show Dustbin Full
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Dustbin Full !");


  } else {

    // LCD show USE ME label
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("USE ME '_'");


    Serial.print("Ultrasonic 0 : ");
    Serial.print(Meas_distance);

    Serial.print(" , Ultrasonic 1 : ");
    Serial.print(Meas_distance1);
    Serial.println(" cm");

  }


  if ( Meas_distance1 < 10 && SMS_count == 0) { // 10 cm, (dustbin full) and SMS count = 0 (no SMS sent before), send SMS


    Serial.println("Sending SMS...");

    //LCD show
    lcd.setCursor(2, 1);
    lcd.println("Sending SMS...");
    delay(5000);
    lcd.clear();

    send_SMS(); // call SMS alert function

    SMS_count++; // increase value of SMS count by 1

  }


  delay(1000); // a bit of delay

}
