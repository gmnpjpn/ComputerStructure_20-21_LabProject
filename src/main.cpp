//---------------------------------------> LIBRARIES
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//---------------------------------------> ESTO NO SÉ QUE HACE
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//---------------------------------------> DEFINES
#define SERVOMIN 320
#define SERVOSTOP 380
#define SERVOMAX 440

#define servo_left 0
#define servo_right 1

#define IR_left 2
#define IR_right 3

#define red_led 12
#define green_led 9

#define pingPin 5

#define button_pin 11


void setup() {
  //---------------------------------------> INITIALIZATION OF SERVOS, IR SENSORS...
  pwm.begin();
  pwm.setPWMFreq(60);

  pinMode (IR_left,INPUT);
  pinMode(IR_right,INPUT);
  Serial.begin(9600);

  pinMode (red_led, OUTPUT);
  pinMode (green_led, OUTPUT);

  pinMode(button_pin, INPUT);


  //---------------------------------------> START SIGNAL WITH LED, IT WILL INDICATE THAT THE ECOBOT STARTS RUNNING
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

//---------------------------------------> METHODS
  void delayMod(){
    delay(0);
  }

  void fastForward() {
    digitalWrite(green_led,HIGH);
    pwm.setPWM(servo_right, 0, SERVOMAX);
    pwm.setPWM(servo_left, 0, SERVOMIN);
    digitalWrite(green_led,LOW);
  }

  void turnRight(){
    digitalWrite(red_led,HIGH);
    pwm.setPWM(servo_right,0,350);
    pwm.setPWM(servo_left,0,SERVOMIN);
    delayMod();
    digitalWrite(red_led,LOW);
  }

  void turnLeft(){
    digitalWrite(red_led,HIGH);
    pwm.setPWM(servo_right,0,SERVOMAX);
    pwm.setPWM(servo_left,0,360);
    delayMod();
    digitalWrite(red_led,LOW);
  }

  void stop(){
    digitalWrite(green_led,LOW);
    pwm.setPWM(servo_right,0,SERVOSTOP);
    pwm.setPWM(servo_left,0,SERVOSTOP);
  }

  void followLine_Right(){
    //---------------------------------------> LINE FOLLOWING CODE (RIGTH SIDE)
    int valor_IR_left = digitalRead(IR_left);
    int valor_IR_right = digitalRead(IR_right);

    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      stop();
    }
    delayMod();
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnRight();
    }
    delayMod();
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
    }
    delayMod();
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      fastForward();
    }
    delayMod();
  }

  void followLine_Left(){
    int valor_IR_left = digitalRead(IR_left);
    int valor_IR_right = digitalRead(IR_right);

    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      stop();
    }
    delayMod();
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnLeft();
    }
    delayMod();
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      fastForward();
    }
    delayMod();
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
    }
    delayMod();
  }

  void followLine_Middle(){
    int valor_IR_left = digitalRead(IR_left);
    int valor_IR_right = digitalRead(IR_right);

    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      stop();
    }
    delayMod();
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      fastForward();
    }
    delayMod();
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
    }
    delayMod();
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
    }
    delayMod();    
  }

  void turn180Degree(){
    turnRight();
  }

  void showMemoryAdressesOfVariables(){
    int valor_IR_left = digitalRead(IR_left);
    int *valorIRleft_Pointer= &valor_IR_left;
    printf("Dirección de memoria de IR izquierdo: %p \n",valorIRleft_Pointer);
    int valor_IR_right = digitalRead(IR_right);
    int *valorIRright_Pointer= &valor_IR_right;
    printf("Dirección de memoria de IR derecho: %p \n",valorIRright_Pointer);
  }


void loop() {
  /*
  //---------------------------------------> ASSIGNATION OF IR VALUES TO IT'S VARIABLES AND IMPRESSION OF THEIR MEMORY ADRESSES
  int valor_IR_left = digitalRead(IR_left);
  int *valorIRleft_Pointer= &valor_IR_left;
  printf("Dirección de memoria de IR izquierdo: %p \n",valorIRleft_Pointer);
  int valor_IR_right = digitalRead(IR_right);
  int *valorIRright_Pointer= &valor_IR_right;
  printf("Dirección de memoria de IR derecho: %p \n",valorIRright_Pointer);
  */


  //---------------------------------------> LIGHT SENSOR THINGS
  int light = analogRead(A0);

  //---------------------------------------> ULTRASOUND SENSOR THINGS
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(10);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = duration / 29 / 2;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);

  //---------------------------------------> BUTTON THINGS
  int button_value = digitalRead(button_pin);
  if (button_value==HIGH){
    pwm.setPWM(servo_right,0,350);
    pwm.setPWM(servo_left,0,SERVOMIN);
  }


  followLine_Middle();

  if (light>=100){followLine_Left;} else {followLine_Right;}
  //CAMBIAR EL VALOR 100 POR LO QUE CORRESPONDA, ES PARA QUE NO DE ERROR SI LO DEJO VACÍO
  
  if (button_value==HIGH){
    turn180Degree();
  }
  
}

//CONFIGURAR LO RELACIONADO CON EL SENSOR DE ULTRASONIDOS PARA QUE ESQUIVE OBSTÁCULOS

//CONFIGURAR EL SENSOR DE LUZ PARA QUE AL DETECTAR EL FLASH, VAYA POR EL BORDE IZQUIERDO Y AL APAGARLO VAYA POR EL BORDE DERECHO