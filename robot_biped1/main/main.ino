#include <IRremote.h>
#include <Servo.h>

// Pins
const int irPin = 5;
const int clockPin = 11;
const int dataPin = 9;
const int latchPin = 10;

// Objects
decode_results results;
IRrecv irrecv(irPin);
Servo headServo;

// Variables
int headAngle = 120;
int currentEyePattern = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600);
  irrecv.enableIRIn();
  headServo.attach(3);
  headServo.write(90);
}

void loop() {
  if(irrecv.decode(&results)) {
//    if(!results.value == 0xFFFFFFFF)
      Serial.println(results.value, HEX);

    switch(results.value) {

      // rotate head
      case 0xFD28D7: // left arrow
        turnHeadLeft();
        break;
      case 0xFD6897: // right arrow
        turnHeadRight();
        break;

      // Eye symbols
      case 0xFD00FF: drawEyeSymbol(1);
                     break;
      case 0xFD807F: drawEyeSymbol(2);
                     break;
      case 0xFD40BF: drawEyeSymbol(3);
                     break;
      case 0xFD20DF: drawEyeSymbol(4);
                     break;
      case 0xFDA05F: drawEyeSymbol(5);
                     break;
      case 0xFD609F: drawEyeSymbol(6);
                     break;
      case 0xFD10EF: drawEyeSymbol(7);
                     break;
      case 0xFD906F: drawEyeSymbol(8);
                     break;
      case 0xFD50AF: drawEyeSymbol(9);
                     break;
      case 0xFDB04F: drawEyeSymbol(0);
                     break;

    }



    irrecv.resume();
  }
}

void setRegister(int numberToDisplay) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
  digitalWrite(latchPin, HIGH);
}

void drawEyeSymbol(int id) {
  // Eye parts coordinates
  //  1 2    4 7
  // 5 3 4  6 5 3
  //  6 7    1 2
  switch(id) {
    case 1: setRegister(0b11111111); //  # #    # #
            setRegister(0b11111111); // # # #  # # #
            break;                   //  # #    # #

    case 2: setRegister(0b00000000); //  . .    . .
            setRegister(0b00000000); // . . .  . . .
            break;                   //  . .    . .

    case 3: setRegister(0b10010100); //  . #    # .
            setRegister(0b01010010); // . . #  # . . >_<
            break;                   //  . #    # .

    case 4: setRegister(0b00110110); //  # #    # #
            setRegister(0b11011000); // # . #  # . # ^_^
            break;                   //  . .    . .

    case 5: setRegister(0b00101100); //  . .    . .
            setRegister(0b00111000); // # # #  # # # -_-
            break;                   //  . .    . .

    case 6: setRegister(0b11110110); //  # #    # #
            setRegister(0b11011110); // # . #  # . # O_O
            break;                   //  # #    # #

    case 7: setRegister(0b00001000); //  . .    . .
            setRegister(0b00100000); // . # .  . # . ·_·
            break;                   //  . .    . .

    case 8: setRegister(0b11100100); //  . .    . .
            setRegister(0b00011110); // # . #  # . # u_u
            break;                   //  # #    # #

    case 9: setRegister(0b00000000); //  . .    . .
            setRegister(0b00000000); // . . .  . . .
            break;                   //  . .    . .

    case 0: setRegister(0b00000000); //  . .    . .
            setRegister(0b00000000); // . . .  . . .
            break;                   //  . .    . .
  }
}

void turnHeadLeft() {
  if(headAngle != 150) {
    for(int i = 0; i < 30; i++) {
      headAngle++;
      headServo.write(headAngle);
      delay(15);
    }
  }
  Serial.println(headAngle);
}

void turnHeadRight() {
  if(headAngle != 30) {
    for(int i = 0; i < 30; i++) {
      headAngle--;
      headServo.write(headAngle);
      delay(15);
    }
  }
  Serial.println(headAngle);
}
