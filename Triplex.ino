
#include "TriangleSet.h"
#include "TriplexWriter.h"
#include "SequenceRoutines.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Configuration Constants

// set the number of levels on the triplex
const int NUM_LEVELS = 2;
// number of sequences
const int NUM_SEQUENCES = 6; //3;
// amount of time for each sequence (1 minutes)
const unsigned long TIME_SEQUENCE = 600000;

// create the TriplexWriters
TriplexWriter triplexWriter1 = TriplexWriter();
TriplexWriter triplexWriter2 = TriplexWriter(0x41);

// Create the Triangle levels that are on the first sheild
// define: TriangleSet(red_pin, green_pin, blue_pin, shield)
TriangleSet set1 = TriangleSet(3, 5, 6, triplexWriter1);
TriangleSet set2 = TriangleSet(9, 10, 11, triplexWriter1);

// Triangles that are on the second shield
//TriangleSet set3 = TriangleSet(3, 5, 6, triplexWriter2);
//TriangleSet set4 = TriangleSet(9, 10, 11, triplexWriter2);

TriangleSet layers[] = {
  set1, set2};

// Define the sequences
SleepingSequence sleepingSeq = SleepingSequence(layers, NUM_LEVELS, 0);
GradualRiseSequence gradualRiseSeq = GradualRiseSequence(layers, NUM_LEVELS, 10);
CycleRiseSequence cycleRiseSeq = CycleRiseSequence(layers, NUM_LEVELS, 1000);
SolidRiseSequence solidRiseSeq = SolidRiseSequence(layers, NUM_LEVELS, 1000);
MovingFadeSequence movingFadeSeq = MovingFadeSequence(layers, NUM_LEVELS, 5, 85);
FadeSequence fadeSeq = FadeSequence(layers, NUM_LEVELS, 5);
SolidSequence aseq = SolidSequence(layers, NUM_LEVELS, 1000);
AbstractSequence *const sequences[NUM_SEQUENCES] = { 
  &gradualRiseSeq, &cycleRiseSeq, &solidRiseSeq, &movingFadeSeq, &fadeSeq, &aseq};
//AbstractSequence *const sequences[1] = {&aseq};

// our state variables
int currentSequence;
unsigned long lastChange;

void setup() {
  currentSequence = 0;
  lastChange = 0;
  //set1.manualWrite(255, 255, 255);
  //delay(1000);
  //sleepingSeq.step();

}

void loop() {
  if (millis() - lastChange > TIME_SEQUENCE) {
    lastChange = millis();

    //TODO should we have something that fires between sequences? or just clear all the lights? 
    sleepingSeq.step();

    currentSequence += 1;
    if (currentSequence > NUM_SEQUENCES) {
      currentSequence = 0;
    }

  }
  sequences[currentSequence]->checkedStep();
}




