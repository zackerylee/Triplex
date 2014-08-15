#include "TriangleSet.h"
#include "TriplexWriter.h"
#include "SequenceRoutines.h"

TriplexWriter triplexWriter = TriplexWriter();

// set the number of levels on the triplex
const int NUM_LEVELS = 2;
TriangleSet set1 = TriangleSet(3, 5, 6, triplexWriter);
TriangleSet set2 = TriangleSet(9, 10, 11, triplexWriter);
TriangleSet layers[] = {set1, set2};
FadeSequence seq;
NewSequence aseq;
AbstractSequence *const sequences[2] = {&seq, &aseq};
const int NUM_SEQUENCES = 2;

void setup() {
  seq = FadeSequence(layers, NUM_LEVELS);
  aseq = NewSequence();
}

void loop() {
  int delayVal = 5;
  seq.step();
  delay(delayVal);
  aseq.step();
  
  AbstractSequence *zzz = sequences[1];
  zzz->step();
}



