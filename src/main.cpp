//-------------------------------------------> LIBRARIES
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//-------------------------------------------> ESTO NO SÉ QUE HACE
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//-------------------------------------------> DEFINES
#define SERVOMIN 320
#define SERVOSTOP 380
#define SERVOMAX 440

#define servo_left 0
#define servo_right 1

#define IR_left 2
#define IR_right 3


void setup() {
  //-------------------------------------------> INITIALIZATION OF SERVOS AND IR SENSORS
  pwm.begin();
  pwm.setPWMFreq(60);

  pinMode (IR_left,INPUT);
  pinMode(IR_right,INPUT);
  Serial.begin(9600);


  //-------------------------------------------> START SIGNAL WITH LED, IT WILL INDICATE THAT THE ECOBOT STARTS RUNNING
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

//-------------------------------------------> METHODS
  void delayMod(){
    delay(0);
  }

  void adelanteRapido() {

    pwm.setPWM(servo_right, 0, SERVOMAX);
    pwm.setPWM(servo_left, 0, SERVOMIN);
  }

  void giroDerecha(){
    pwm.setPWM(servo_right,0,350);
    pwm.setPWM(servo_left,0,SERVOMIN);
    delayMod();
  }

  void giroIzquierda(){
    pwm.setPWM(servo_right,0,SERVOMAX);
    pwm.setPWM(servo_left,0,360);
    delayMod();
  }

  void stop(){
    pwm.setPWM(servo_right,0,SERVOSTOP);
    pwm.setPWM(servo_left,0,SERVOSTOP);
  }


void loop() {
  //-------------------------------------------> ASSIGNATION OF IR VALUES TO IT'S VARIABLES
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);

  //-------------------------------------------> LINE FOLLOWING CODE
  if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    stop();
  }
  delayMod();
  if(valor_IR_left==LOW  && valor_IR_right==LOW){
    adelanteRapido();
  }
  delayMod();
  if (valor_IR_left==HIGH && valor_IR_right==LOW){
    giroDerecha();
  }
  delayMod();
  if (valor_IR_left==LOW && valor_IR_right==HIGH){
    giroIzquierda();
  }
  delayMod();
}
