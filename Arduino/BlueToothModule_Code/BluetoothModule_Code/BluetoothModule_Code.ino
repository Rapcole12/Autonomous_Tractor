#include "Arduino.h"
#include <SoftwareSerial.h>

int IN1 = 4;
int IN2 = 5;
int IN3 = 6;
int IN4 = 7;
int Rx = 8; 
int Tx = 9;
SoftwareSerial BTModule(Rx, Tx);
int FORWARD = 1;
int STOP = 0;
int DIRECTION = STOP;

void setup() {
  //set Rx and Tx pins 
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(Rx, OUTPUT); 
  pinMode(Tx, INPUT); 
  resetPins();
  BTModule.begin(9600); 
  Serial.begin(9600); 

}


void loop() {
  // put your main code here, to run repeatedly:
  while (BTModule.available() > 0){
     // String string_message  = (String) BTModule.read(); //typecast the Value read from the BTModule to be a character as well 
      int read_Tx = digitalRead(Tx); 
      if(read_Tx == LOW){ 
         
         DIRECTION = !DIRECTION;  // Toggle 0 to 1 or 1 to 0;
         motorA(DIRECTION);
         motorB(DIRECTION);

      }
      
      /*
      if(string_message == Turn_Off){ 
         motorA(DIRECTION);
         motorB(DIRECTION);        

      }
      */

  }

}

void motorA(int status) {
  if (status == STOP) {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor A Clockwise (Forward)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  }
  else{
    return;
  }
}

void motorB(int status) {
  if (status == STOP) {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  else if (status == FORWARD) {
    // Turn Motor B Counterclockwise (Forward)
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
  else {
    return;
  }
}

void resetPins() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    digitalWrite(Tx, LOW);
}
