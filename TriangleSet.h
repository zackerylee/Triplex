
#ifndef TriangleSet_H
#define TriangleSet_H

#include "TriplexWriter.h"

class TriangleSet {
public:
	TriangleSet(int rPin, int gPin, int bPin, TriplexWriter &triplexWriter);
	void goRed();
	void goBlue();
	void goGreen();
	void goFull();
	void goZero();
	void manualWrite(int red, int green, int blue);

private:
	int _rPin;
	int _gPin;
	int _bPin;
	TriplexWriter writer;
};

#endif