#include "TriangleSet.h"
#include "TriplexWriter.h"
#include "SequenceRoutines.h"

// Configuration Constants

// set the number of levels on the triplex
const int NUM_LEVELS = 2;
// number of sequences
const int NUM_SEQUENCES = 2;
// amount of time for each sequence (1 minutes)
const unsigned long TIME_SEQUENCE = 60000;

// create the TriplexWriters
TriplexWriter triplexWriter1 = TriplexWriter();
//TriplexWriter triplexWriter2 = TriplexWriter(0x41);

// Create the Triangle levels
TriangleSet set1 = TriangleSet(3, 5, 6, triplexWriter1);
TriangleSet set2 = TriangleSet(9, 10, 11, triplexWriter1);
TriangleSet layers[] = {set1, set2};

// Define the sequences
FadeSequence seq = FadeSequence(layers, NUM_LEVELS, 50);
SolidSequence aseq = SolidSequence(layers, NUM_LEVELS, 1000);
AbstractSequence *const sequences[2] = {&seq, &aseq};
//AbstractSequence *const sequences[1] = {&aseq};

// our state variables
int currentSequence;
unsigned long lastChange;

void setup() {
  currentSequence = 0;
  lastChange = 0;
}

void loop() {
  if (millis() - lastChange > TIME_SEQUENCE) {
    lastChange = millis();
    
    //TODO should we have something that fires between sequences? or just clear all the lights? 
    
    currentSequence += 1;
    if (currentSequence > NUM_SEQUENCES) {
      currentSequence = 0;
    }
    
  }
  int delayVal = 50;
  sequences[currentSequence]->step();
}



