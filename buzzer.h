// buzzer.h
// Code used to make sounds.
#pragma once
#include "pitches.h"

// I have only one buzzer pin, so why should I waste my time writing it all
// over again?
#define buzz(freq, duration) TimerFreeTone(buzzerPin, freq, duration)

// Play a melody.
// TODO: fix the bug when a melody does not play fully
void play(int *melody, int *noteDurations, int notesCount) {
  for(int thisNote = 0;
      // `sizeof` returns size in bytes, so I have to divide it by byte size of 
      // one element.
      thisNote < notesCount;
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

// Melody played when Crêepe is not in moving mode and sees anything,
int melody_sayHello[8] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations_sayHello[8] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
#define sayHello() play(melody_sayHello, noteDurations_sayHello, 8)

// Melody played when Crêepe starts,
int melody_notifyStart[5] = {
  NOTE_C2, NOTE_C4, NOTE_A2, 0, NOTE_C2
};
int noteDurations_notifyStart[5] = {
  4, 4, 2, 2, 8
};
#define notifyStart() play(melody_notifyStart, noteDurations_notifyStart, 5)

// Melody played when Crêepe is in moving mode and sees anything.
// TODO: make it more swearing-like
// TODO: do not allow to swear more than one time at a time (one swearing for
// step or kinda like that)
long lastSwearingTime = millis();
bool swornAlready = false;
int melody_swearInFrench[] = {
  NOTE_A5, NOTE_B1
};
int noteDurations_swearInFrench[] = {
  4, 2
};
void swearInFrench() {
  if(millis() - lastSwearingTime < 30000 || swornAlready) return;
  play(melody_swearInFrench, noteDurations_swearInFrench, 2);
  swornAlready = true;
  lastSwearingTime = millis();
}


