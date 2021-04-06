//FROM LINE 3 TO LINE 14: COPY-PASTE ALWAYS
//-------------------------------------------------------------------------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 320
#define SERVOSTOP 380
#define SERVOMAX 440

#define servo_left 0
#define servo_right 1
//-------------------------------------------------------------------------------------------------------------------------------


void setup() {
//THE CODE THAT I INTRODUCE HERE RUNS ONLY WHEN I POWER ON THE ECOBOT

//LINES 22 AND 23: COPY-PASTE ALWAYS
  pwm.begin();
  pwm.setPWMFreq(60);

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
//THE CODE THAT I INTRODUCE HERE RUNS REPETEADLY

//IT MAKES THE ECOBOT DRIVE STRAIGHT
//-------------------------------------------------------------------------------------------------------------------------------
  pwm.setPWM(servo_left, 1, SERVOMIN);
  pwm.setPWM(servo_right, 1, SERVOMAX);
//-------------------------------------------------------------------------------------------------------------------------------
}