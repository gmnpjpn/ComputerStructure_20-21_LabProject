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

boolean buttonState=false;
 void turn180degree(){
    buttonState=true;
  }

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

  attachInterrupt(digitalPinToInterrupt(button_pin),turn180degree,RISING);
  int button_value = digitalRead(button_pin);

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


void loop(){
  //TIME STARTS
  float time = millis();
  Serial.println(time/1000);
  
  int valor_IR_left = digitalRead(IR_left);
  int valor_IR_right = digitalRead(IR_right);
  int light = analogRead(A0);

  //LIGHT AND MOVEMENT FEATURES, IT'S A COPY
  if(light<600 && light>250){
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
  } else if(light>600){
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
  if (buttonState){
    digitalWrite(red_led,HIGH);
    digitalWrite(green_led,LOW);
    pwm.setPWM(servo_right,0,SERVOMAX);
    pwm.setPWM(servo_left,0,SERVOMAX);
    delay(1450);
    digitalWrite(red_led,LOW);
    digitalWrite(green_led,HIGH);
    buttonState=false;
  }

  //TIME FINISH
  if (time < 100){
    Serial.print("Tiempo De Loop: ");
    Serial.println(time);
  }
}