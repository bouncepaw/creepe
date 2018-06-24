#pragma once
#include "pitches.h"

// I have only one buzzer pin, so why should I waste my time writing it all
// over again?
#define buzz(freq, duration) TimerFreeTone(buzzerPin, freq, duration)

void play(int *melody, int *noteDurations) {
  for(int thisNote = 0;
      // `sizeof` returns size in bytes, so I have to divide it by byte size of one
      // element.
      thisNote < sizeof(melody) / sizeof(melody[0]);
      thisNote++) {

    // To calculate the note duration, divide one second by the note type.
    // quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    buzz(melody[thisNote], noteDuration);

    // To distinguish the notes, set a minimum time between them.
    // The note's duration + 30% seems to work well:
    delay(noteDuration * 1.3);
  }
}

int melody_sayHello[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations_sayHello[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
#define sayHello() play(melody_sayHello, noteDurations_sayHello)

int melody_notifyStart[] = {
  NOTE_C2, NOTE_C4, NOTE_A2, 0, NOTE_C2
};
int noteDurations_notifyStart[] = {
  4, 4, 2, 2, 8
};
#define notifyStart() play(melody_notifyStart, noteDurations_notifyStart)

long lastSwearingTime = millis();
int melody_swearInFrench[] = {
  NOTE_B4, NOTE_B3, 0, NOTE_A3, NOTE_A5
};
int noteDurations_swearInFrench[] = {
  4, 4, 2, 4, 2
};
void swearInFrench() {
  if(millis() - lastSwearingTime < 3000) return;
  play(melody_swearInFrench, noteDurations_swearInFrench);
  lastSwearingTime = millis();
}


