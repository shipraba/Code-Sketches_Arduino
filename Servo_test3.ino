/*
 * Creation & Computation - Digital Futures, OCAD University
 * Kate Hartman / Nick Puckett
 * 
 */

#include <Servo.h>

int servoPin1 = 2; 
int servoPin2 = 3; 
int servoPin3 = 5; 
int servoPin4 = 6;      //Pin that the servo is attached to.
int moveRate = 40;      //the time between updates in milliseconds
int minAngle = 40;      //sets the low point of the movement range
int maxAngle = 180;     //sets the high point of the movement range
int moveIncrement = 1;  // how much to move the motor each cycle
int servoAngle1;

int ledPin1 = 16;    
int ledPin2 = 17;  
int ledPin3 = 11;  
int ledPin4 = 12;         //Pin that the led is attached to - check that it is a PWM pin  
int fadeRate = 20;        //the time between updates in milliseconds
int minBrightVal = 60;     //sets the low point of the fade range
int maxBrightVal = 220;   //sets the high point of the fade range
int fadeIncrement = 1;    // how much to change the brightness each cycle 
int ledBrightness;
long lastTimeYouChanged;

long lastTimeYouMoved1;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;  // create the Servo objects

int ldrPin = A7;
int ldrValue;
int ldrMin = 500;
int ldrMax = 1023;

void setup() {
  servo1.attach(servoPin1);
  servo2.attach(servoPin2); 
  servo3.attach(servoPin3);
  servo4.attach(servoPin4); //attach the servo to the corresponding control pin
  servoAngle1 = minAngle;
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT); //Set the pin to output mode
  ledBrightness = minBrightVal;

  Serial.begin(9600);
}

void loop() {

  ldrValue = analogRead(ldrPin);
  Serial.println(ldrValue);

if(millis()-lastTimeYouChanged>=fadeRate) 
{
    analogWrite(ledPin1,ledBrightness);
    analogWrite(ledPin2,ledBrightness);  
    analogWrite(ledPin3,ledBrightness);    
    analogWrite(ledPin4,ledBrightness); 
     
    if (ldrValue >= ldrMin && ldrValue <= ldrMax)
     { 
     ledBrightness += fadeIncrement;
     }


     if (ledBrightness <= minBrightVal || ledBrightness >= maxBrightVal) 
     {
    fadeIncrement = -fadeIncrement;
  }
  lastTimeYouChanged = millis(); 
}


  if (millis() - lastTimeYouMoved1 >= moveRate)  
  {       
    if (ldrValue >= ldrMin && ldrValue <= ldrMax)
     { servoAngle1 += moveIncrement;

     }

    if (servoAngle1 <= minAngle || servoAngle1 >= maxAngle) {
      moveIncrement = -moveIncrement;
    }

    servo1.write(servoAngle1); 
    servo2.write(servoAngle1); 
    servo3.write(servoAngle1); 
    servo4.write(servoAngle1);  //write the value to the servo

    lastTimeYouMoved1 = millis();  //save the value in time that this switch occured, so we can use it again.
  }
}
