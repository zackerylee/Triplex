
#include "TriangleSet.h"
#include "TriplexWriter.h"
#include "SequenceRoutines.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Configuration Constants
#define SHIELD_1 0x40
#define SHIELD_2 0x41

// set the number of levels on the triplex
const int NUM_LEVELS = 9;
// number of sequences
const int NUM_SEQUENCES = 7; //3;
// amount of time for each sequence (1 minutes)
const unsigned long TIME_SEQUENCE = 30000;
// power 0=100%, 1228=70%
const int POWER = 3500;

// create the TriplexWriters
TriplexWriter triplexWriter1 = TriplexWriter(SHIELD_1, POWER);
TriplexWriter triplexWriter2 = TriplexWriter(SHIELD_2, POWER);

// Create the Triangle levels that are on the first sheild
// define: TriangleSet(red_pin, green_pin, blue_pin, shield)
TriangleSet set1 = TriangleSet(0, 1, 2, triplexWriter1);
TriangleSet set2 = TriangleSet(3, 4, 5, triplexWriter1);
TriangleSet set3 = TriangleSet(6, 7, 8, triplexWriter1);
TriangleSet set4 = TriangleSet(9, 10, 11, triplexWriter1);
TriangleSet set5 = TriangleSet(12, 13, 14, triplexWriter1);


// Triangles that are on the second shield
//TriangleSet set3 = TriangleSet(3, 5, 6, triplexWriter2);
//TriangleSet set4 = TriangleSet(9, 10, 11, triplexWriter2);
TriangleSet set7 = TriangleSet(0, 1, 2, triplexWriter2);
TriangleSet set8 = TriangleSet(3, 4, 5, triplexWriter2);
TriangleSet set9 = TriangleSet(6, 7, 8, triplexWriter2);
TriangleSet set6 = TriangleSet(9, 10, 11, triplexWriter2);


TriangleSet topTriangle = TriangleSet(12, 13, 14, triplexWriter2);

TriangleSet layers[] = {
  set1,
  set2,
  set3,
  set4,
  set5, 
  set6,
  set7,
  set8,
  set9
};

// Define the sequences
SleepingSequence sleepingSeq = SleepingSequence(layers, NUM_LEVELS, 0);
GradualRiseSequence gradualRiseSeq = GradualRiseSequence(layers, NUM_LEVELS, 10);
CycleRiseSequence cycleRiseSeq = CycleRiseSequence(layers, NUM_LEVELS, 1000);
SolidRiseSequence solidRiseSeq = SolidRiseSequence(layers, NUM_LEVELS, 1000);
MovingFadeSequence movingFadeSeq = MovingFadeSequence(layers, NUM_LEVELS, 5, 85);
FadeSequence fadeSeq = FadeSequence(layers, NUM_LEVELS, 5);
SolidSequence aseq = SolidSequence(layers, NUM_LEVELS, 1000);
RandomSequence randomSeq = RandomSequence(layers, NUM_LEVELS, 1000);
AbstractSequence *const sequences[NUM_SEQUENCES] = { 
   &cycleRiseSeq, &gradualRiseSeq, &solidRiseSeq, &movingFadeSeq, &fadeSeq, &aseq, &randomSeq};
//AbstractSequence *const sequences[1] = {&sleepingSeq};

// our state variables
int currentSequence;
unsigned long lastChange;

void setup() {
  Serial.begin(9600);
  Serial.println("initialize triplex");

  currentSequence = 0;
  lastChange = 0;
  triplexWriter1.setup();
  triplexWriter2.setup();

  // make the top triangle white
  topTriangle.manualWrite(100, 100, 100);
}

void loop() {
  if (millis() - lastChange > TIME_SEQUENCE) {
    Serial.println("loop()");

    lastChange = millis();

    //TODO should we have something that fires between sequences? or just clear all the lights? 
    //sleepingSeq.step();

    currentSequence += 1;
    if (currentSequence >= NUM_SEQUENCES) {
      currentSequence = 0;
    }

  }
  sequences[currentSequence]->checkedStep();
}


