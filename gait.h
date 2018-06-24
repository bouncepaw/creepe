// Gait.h
// Gait, movement and everything like that for Crêepe.
#pragma once
#include "Arduino.h"
#include "angle_set.h"

#define times(numberOfTimes) for(int t = 0; t < (numberOfTimes); t++)

unsigned long lastBlind;

// Variable names below do not need any clarification

void stayStraight() {
  tlrV(151, 25);
  tlH(90);
  trH(140);

  Serial.println("Stood straight.");
}

// TODO: fix the bug when Crêepe instead of staying straight in the end stays
// weirdly.
void waveHand() {
  if(millis() - lastBlind < 2000) return;
  Serial.println("Waved hand.");
  sayHello();
  setRight(100, 100);
  setLeft(10, 0);

  delay(60);
  times(3) {
    tlH(120);
    tlH(0);
  }

  stayStraight();
  lastBlind = millis();
}

void rotateLeft() {
  tlrV(0, 180);
  tlrH(180, 180);
  stayStraight();
  Serial.println("Rotated left.");
}

void rotateRight() {
  tlrV(0, 180);
  tlrH(30, 30);
  stayStraight();
  Serial.println("Rotated right.");
}

void stepBackward() {
  tlrV(90, 90);
  setElbows(151, 25);
  // stayStraight();
  // tlrV(0, 180);
  // leftElbow.write(151);
  // rightElbow.write(25);
  Serial.println("Took a step backward.");
}

void stepForward() {
  leftElbow.write(0);
  rightElbow.write(180);
  stayStraight();
  Serial.println("Took a step forward.");
}
