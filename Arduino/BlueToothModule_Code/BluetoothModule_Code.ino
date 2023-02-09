#include "Arduino.h"
#include <SoftwareSerial.h>

const int Rx = 8; 
const int Tx = 9;
SoftwareSerial BTModule(Rx, Tx);

void setup() {
  //set Rx and Tx pins 
  pinMode(Rx, INPUT); 
  pinMode(Tx, OUTPUT); 
  BTModule.begin(9600); 
  Serial.begin(9600); 

}

String Turn_On = "On"; 
String Turn_Off = "Off";

void loop() {
  // put your main code here, to run repeatedly:
  while (BTModule.available() > 0){
      String string_message  = (String) BTModule.read(); //typecast the Value read from the BTModule to be a character as well 
      
      if(string_message == Turn_On){ 



      }

      if(string_message == Turn_Off){ 

      }
  }

}
