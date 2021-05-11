//---------------------------------------> LIBRARIES
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

//---------------------------------------> ADAFRUIT
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

#define SERVO_45deg 300
#define SERVO_90deg 420
#define SERVO_135deg 540

int servo_180=2;

unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempoSegundos = 0;


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

  tiempo1 = millis();


  //---------------------------------------> START SIGNAL WITH LED, IT WILL INDICATE THAT THE ECOBOT STARTS RUNNING
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

//---------------------------------------> METHODS
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
  digitalWrite(red_led,LOW);
}

void turnLeft(){
  digitalWrite(red_led,HIGH);
  pwm.setPWM(servo_right,0,SERVOMAX);
  pwm.setPWM(servo_left,0,360);
  digitalWrite(red_led,LOW);
}

void stop(){
  digitalWrite(green_led,LOW);
  pwm.setPWM(servo_right,0,SERVOSTOP);
  pwm.setPWM(servo_left,0,SERVOSTOP);
}

void followLine_Right(){
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);

  if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    turnLeft();
  }
  if(valor_IR_left==LOW  && valor_IR_right==LOW){
    turnRight();
  }
  if (valor_IR_left==HIGH && valor_IR_right==LOW){
    turnRight();
  }
  if (valor_IR_left==LOW && valor_IR_right==HIGH){
    fastForward();
  }
}

void followLine_Left(){
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);

  if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    turnRight();
  }
  if(valor_IR_left==LOW  && valor_IR_right==LOW){
    turnLeft();
  }
  if (valor_IR_left==HIGH && valor_IR_right==LOW){
    fastForward();
  }
  if (valor_IR_left==LOW && valor_IR_right==HIGH){
    turnLeft();
  }
}

void followLine_Middle(){
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);

  if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    stop();
  }
  if(valor_IR_left==LOW  && valor_IR_right==LOW){
    fastForward();
  }
  if (valor_IR_left==HIGH && valor_IR_right==LOW){
    turnRight();
  }
  if (valor_IR_left==LOW && valor_IR_right==HIGH){
    turnLeft();
  }    
}

void lightSensorFeature(){
  int light = analogRead(A0);
  if (light>=600){
    followLine_Left();
  } else {
    followLine_Right();
  }
}

void turn180Degree(){ //WE HAVE TO TRY THAT FUNCTION, AND SEE IF THE LEDS WORK PROPERLY
  do{
    turnRight();
  } while (millis()<=5000);
}

void turn180WhenButtonIsPressed(){
  int button_value = digitalRead(button_pin);
  if (button_value == HIGH) {
     turnRight();
  }
}

void followLineMiddle_And_lightFeatures(){
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);
  int light = analogRead(A0);

  if(light<500 && light>250){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnLeft();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      fastForward();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
    }
  } else if(light>500){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnLeft();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnRight();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      fastForward();
    }
  } else if(light<250){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnRight();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnLeft();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      fastForward();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
    }      
  } else{
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    turnRight();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
    turnLeft();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
    fastForward();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
    turnLeft();
    }
  }
}

void lightMeasure(){
  int light = analogRead(A0);
  Serial.print("\nLight: ");
  Serial.print(light);
  delay(200);
}

void obstacleDetection(){ // THAT'S THE EXAMPLE CODE, WE HAVE TO IMPLEMENT IT
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(10);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  duration= pulseIn(pingPin, HIGH);
  cm = duration / 29 / 2;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(100);

  //SET SENSOR IN DEFAULT POSITION
  pwm.setPWM(servo_180, 0, SERVO_90deg);
  if (cm<10){
     pwm.setPWM(servo_180, 0, SERVO_135deg);
     if (cm<10){
      
     }
  } else{
    followLineMiddle_And_lightFeatures();
  }



  // Posición 45º
  pwm.setPWM(servo_180, 0, SERVO_45deg);
  delay(2000);
  // Posición 90º
  pwm.setPWM(servo_180, 0, SERVO_90deg);
  delay(2000);
  // Posición 135º
  pwm.setPWM(servo_180, 0, SERVO_135deg);
  delay(2000);
}



void finalECoBot(){
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);
  int light = analogRead(A0);

  //LIGHT AND MOVEMENT FEATURES
  if(light<500 && light>250){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnLeft();
      int button_value = digitalRead(button_pin); 
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      fastForward();
      int button_value = digitalRead(button_pin);  
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
      int button_value = digitalRead(button_pin);     
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
      int button_value = digitalRead(button_pin);      
    }
  } else if(light>500){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnLeft();

    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnRight();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      turnRight();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      fastForward();
    }
  } else if(light<250){
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
      turnRight();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
      turnLeft();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
      fastForward();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
      turnLeft();
    }      
  } else{
    if(valor_IR_left==HIGH && valor_IR_right==HIGH){
    turnRight();
    }
    if(valor_IR_left==LOW  && valor_IR_right==LOW){
    turnLeft();
    }
    if (valor_IR_left==HIGH && valor_IR_right==LOW){
    fastForward();
    }
    if (valor_IR_left==LOW && valor_IR_right==HIGH){
    turnLeft();
    }
  }

  //BUTTON FEATURE
  int button_value = digitalRead(button_pin);
  if (button_value == HIGH) {
    turn180Degree();
  }

  //OBSTACLE DETECTION FEATURE
  
  
}

void showMemoryAdresses(){
  int variableInt= 4;
  int *p_variableInt= &variableInt; 
  double variableDouble= 4.67;
}

void time(){
  tiempo2 = millis();
  if(tiempo2 > (tiempo1+1000)){  //Si ha pasado 1 segundo ejecuta el IF
  tiempo1 = millis(); //Actualiza el tiempo actual
  tiempoSegundos = tiempo1/1000;
  Serial.print("Han transcurrido ");
  Serial.print(tiempoSegundos);
  Serial.println(" segundos de tiempo de ejecución");
  }
}


void loop(){
  float time = millis();









  if (time < 100){
    Serial.println(time);
  }
}