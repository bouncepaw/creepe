#pragma once
#include "Arduino.h"

void tGeneric(Servo servo, int finalPosition) {
  for(int i = servo.read() > finalPosition ? -1 : 1;
      servo.read() != finalPosition;
      delay(1))
    servo.write(constrain(servo.read() + i, 0, 180));
}

// Turn arms to a certain angle
// t(l|r)(H|V)
#define tlH(finalPosition) tGeneric(leftShoulder, finalPosition)
#define tlV(finalPosition) tGeneric(leftElbow, finalPosition)
#define trH(finalPosition) tGeneric(rightShoulder, finalPosition)
#define trV(finalPosition) tGeneric(rightElbow, finalPosition)

// Increment servos
// i(l|r)(U|D|L|R)
#define ilU() tlV(leftElbow.read() - 1)
#define ilD() tlV(leftElbow.read() + 1)
#define ilL() tlH(leftShoulder.read() + 1)
#define ilR() tlH(leftShoulder.read() - 1)

#define irU() trV(rightElbow.read() - 1)
#define irD() trV(rightElbow.read() + 1)
#define irL() trH(rightShoulder.read() + 1)
#define irR() trH(rightShoulder.read() - 1)

void tlrV(int leftFinalPosition, int rightFinalPosition) {
  while(leftElbow.read() != leftFinalPosition &&
      rightElbow.read() != rightFinalPosition) {
    leftElbow.read() > leftFinalPosition ? ilU() : ilD();
    rightElbow.read() > rightFinalPosition ? irU() : irD();
  }
}
void tlrH(int leftFinalPosition, int rightFinalPosition) {
  while(leftShoulder.read() != leftFinalPosition &&
      rightShoulder.read() != rightFinalPosition) {
    leftShoulder.read() > leftFinalPosition ? ilR() : ilL();
    rightShoulder.read() > rightFinalPosition ? irR() : irL();
  }
}

void setElbows(int leftElbowAngle, int rightElbowAngle) {
  leftElbow.write(leftElbowAngle);
  rightElbow.write(rightElbowAngle);
}

void setShoulders(int leftShoulderAngle, int rightShoulderAngle) {
  leftShoulder.write(leftShoulderAngle);
  rightShoulder.write(rightShoulderAngle);
}

void setLeft(int leftElbowAngle, int leftShoulderAngle) {
  leftElbow.write(leftElbowAngle);
  leftShoulder.write(leftShoulderAngle);
}

void setRight(int rightElbowAngle, int rightShoulderAngle) {
  rightElbow.write(rightElbowAngle);
  rightShoulder.write(rightShoulderAngle);
}
