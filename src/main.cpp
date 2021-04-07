

//BLOCK BELOW: COPY-PASTE ALWAYS
//-------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//SERVOS DEFINED
#define SERVOMIN 320
#define SERVOSTOP 380
#define SERVOMAX 440

#define servo_left 0
#define servo_right 1

//INFRARED SENSOR DEFINED
#define IR_left 2
#define IR_right 3
//-------------------------------------------------------------------------------------------------------------------------------


void setup() {
//TWO LINES BELOW: SERVO THINGS
  pwm.begin();
  pwm.setPWMFreq(60);

//TWO LINES BELOW: IR THINGS
  pinMode (IR_left,INPUT);
  pinMode(IR_right,INPUT);
  Serial.begin(9600);

//-------------------------------------------------------------------------------------------------------------------------------
//INITIALIZE LED AS AN OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
//LED ON
  digitalWrite(LED_BUILTIN, HIGH);
//WAIT FOR TWO SECONDS
  delay(2000);
//LED OFF
  digitalWrite(LED_BUILTIN, LOW);
//THIS SIGNAL WITH THE LED WILL INDICATE THAT THE ECOBOT IS READY TO EXECUTE THE COMMANDS THAT WE PROGRAM IT
//-------------------------------------------------------------------------------------------------------------------------------
}

void loop() {
//IT MAKES THE ECOBOT DRIVE STRAIGHT
//-------------------------------------------------------------------------------------------------------------------------------
  pwm.setPWM(servo_left, 1, SERVOMIN);
  pwm.setPWM(servo_right, 1, SERVOMAX);
//-------------------------------------------------------------------------------------------------------------------------------


//IT MAKES THE ECOBOT DETECT SOMETHING WITH THE IR SENSOR
//-------------------------------------------------------------------------------------------------------------------------------
int valor_IR_left = digitalRead(IR_left);
int valor_IR_right = digitalRead(IR_right);

Serial.print("IR_left: ");
Serial.print(valor_IR_left);

Serial.print("\t");

Serial.print("IR_right: ");
Serial.println(valor_IR_right);

delay(100);
//-------------------------------------------------------------------------------------------------------------------------------
}