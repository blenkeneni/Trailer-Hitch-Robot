#include <XBOXRECV.h>
#include "pitches.h"                    //need to make this header file

const int actrCtrlPin1 = 2;             //Pin to control actuator movement
const int actrCtrlPin2 = 3;             //Pin to control actuator movement
const int hallSensorPin = A0;           //Pin to read Hall Effect Sensor

const int limitTop = 100;               //Value from Hall Effect Sensor for max extension
const int limitBot = 0;                 //Value from Hall Effect Sensor for max retraction

int motorDir = 8; //Dir 1
int motorSpeed = 9; //PWM 1
int motorDir2 = 10; //Dir 2
int motorSpeed2 = 11; //PWM2
int buzzer = 13; //buzzer on pin 13

//these outputs are all for testing purposes 
int forwardLED = 1; 
int leftLED = 2;
int rightLED = 3;
int upLED = 4; 
int downLED = 5; 
int stopLED = 6;

int melody[] = {                         //select the notes you want to play
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 
};

int noteDurations[] = {                 //4= quarter note, 8 = either note
   4, 8, 8, 4, 4, 4, 4, 4
};

USB Usb;
XBOXRECV Xbox(&Usb);

void setup() {
  Serial.begin(115200);
  Usb.Init(); 
  pinMode(actrCtrlPin1, OUTPUT);
  pinMode(actrCtrlPin2, OUTPUT);
  pinMode(motorDir, OUTPUT); //Movement Part
  pinMode(motorDir2, OUTPUT); //Movement Part
  pinMode(motorSpeed, OUTPUT); //Movement Part
  pinMode(motorSpeed2, OUTPUT); //Movement Part
  
  pinMode(buzzer, OUTPUT); //buzzer
  pinMode(forwardLED, OUTPUT);
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  pinMode(upLED, OUTPUT);
  pinMode(downLED, OUTPUT);
  pinMode(stopLED, OUTPUT);
  
}

void loop() {
  Usb.Task();
  if (Xbox.XboxReceiverConnected) {
    int pos = analogRead(hallSensorPin);                  //Get actuator vertical position
    if (Xbox.getAnalogHat(RightHatY , 0) > 1000) {        //Check if Right Stick is in up direction
      if (pos < limitTop) {                               //Check if actuator can extend
        actuatorUp();      
      } else {
        actuatorHold();     
      }
    } 
    else if(Xbox.getAnalogHat(RightHatY, 0) < 1000) {   //Check if Right Stick is in down direction
      if (pos > limitBot) {                               //Check if actuator can retract
        actuatorDown();     
      } 
      else {
        actuatorHold();
      }
    } 
    else if(Xbox.getAnalogHat(LeftHatY, 0) > 1000) {
      //going forward
      
    } 
    else if(Xbox.getAnalogHat(LeftHatY, 0) < 1000) {   //Check if Right Stick is in down direction
      //going backwards
      //buzzard
    }
    else if(Xbox.getAnalogHat(LeftHatX, 0) > 1000) {
      //going right???
    } 
    else if(Xbox.getAnalogHat(LeftHatX, 0) < 1000) {   //Check if Right Stick is in down direction
      //going left???
    }
    else {                                              //If Right Stick is not moved
      actuatorHold();
    }
    delay(1);
  }
delay(1);
}

void actuatorUp() {
  digitalWrite(actrCtrlPin1, HIGH);
  digitalWrite(actrCtrlPin2, LOW);
  digitalWrite(upLED, HIGH);
}

void actuatorDown() {
  digitalWrite(actrCtrlPin1, LOW);
  digitalWrite(actrCtrlPin2, HIGH);
  digitalWrite(downLED, HIGH);
}

void actuatorHold() {
  digitalWrite(actrCtrlPin1, LOW);
  digitalWrite(actrCtrlPin2, LOW);
}

for (int thisNote = 0; thisNote < 8; thisNote++) {

    //use this to calculate noteDuration: quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(13);
  }

//Stephanie Stuff for movement
