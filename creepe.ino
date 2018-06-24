#include <TimerFreeTone.h>
#include <Ultrasonic.h>
#include <Servo.h>
#include <IRremote.h>

// Pins
#define irrecvPin A2
#define irrecvGndPin A3
#define irrecvVccPin A4
#define echoPin A1
#define trigPin A0
#define buzzerPin 11

// Objects
Servo leftElbow;
Servo leftShoulder;
Servo rightElbow;
Servo rightShoulder;

IRrecv irrecv(irrecvPin);
decode_results results;
Ultrasonic eyes(trigPin, echoPin);

// Variables
unsigned int distance;
bool robotIsInMovingMode = true;

#include "buzzer.h"
#include "gait.h"
#include "angle_set.h"

void setup() {
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(irrecvGndPin, LOW);
  digitalWrite(irrecvVccPin, HIGH);
  irrecv.enableIRIn();

  Serial.begin(9600);

  leftElbow.attach(10);
  leftShoulder.attach(9);
  rightElbow.attach(5);
  rightShoulder.attach(6);

  stayStraight();
  notifyStart();
}

void loop() {
  handleIR();
  look();
}

void look() {
  if(eyes.distanceRead() > 10 && eyes.distanceRead() < 15)
    (robotIsInMovingMode ? swearInFrench() : waveHand());
}

void handleIR() {
  if(irrecv.decode(&results)) {
    Serial.print("Got IR signal: ");
    Serial.println(results.value, HEX);

    switch(results.value) {

      case 0xFD28D7: // left arrow
        if(robotIsInMovingMode) rotateLeft();
        break;
      case 0xFD6897: // right arrow
        if(robotIsInMovingMode) rotateRight();
        break;

      case 0xFD8877: // up arrow
        if(robotIsInMovingMode) stepForward();
        break;
      case 0xFD9867: // down arrow
        if(robotIsInMovingMode) stepBackward();
        break;

      case 0xFD00FF: // number 1
        Serial.println("Number 1 is pressed. Moving mode is on now.");
        robotIsInMovingMode = true; 
        break;
      case 0xFD807F: // number 2
        Serial.println("Number 2 is pressed. Moving mode is off now.");
        robotIsInMovingMode = false;
        break;
        /*
           case 0xFD40BF: break; // 3
           case 0xFD20DF: break;
           case 0xFDA05F: break;
           case 0xFD609F: break;
           case 0xFD10EF: break;
           case 0xFD906F: break;
           case 0xFD50AF: break; // 9
           case 0xFDB04F: break; // 0
         */
    }

    irrecv.resume();
  }
}
