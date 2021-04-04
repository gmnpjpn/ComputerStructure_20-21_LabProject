#include <Arduino.h>

void setup() {
  //THE CODE THAT I INTRODUCE HERE RUNS ONLY WHEN I POWER ON THE ECOBOT

  //INITIALIZE LED AS AN OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);

  //LED ON
  digitalWrite(LED_BUILTIN, HIGH);

  //WAIT FOR TWO SECONDS
  delay(2000);

  //LED OFF
  digitalWrite(LED_BUILTIN, LOW);

  //THIS SIGNAL WITH THE LED WILL INDICATE THAT THE ECOBOT IS READY TO EXECUTE THE COMMANDS THAT WE PROGRAM IT
}

void loop() {
  // put your main code here, to run repeatedly:
}