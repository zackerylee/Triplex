#include "TriangleSet.h"



TriangleSet::TriangleSet(int rPin, int gPin, int bPin, TriplexWriter &triplexWriter) {
	_rPin = rPin;
	_gPin = gPin;
	_bPin = bPin;
	writer = triplexWriter;
}

void TriangleSet::goRed() {
	writer.write(_rPin, 0);
	writer.write(_gPin, 255);
	writer.write(_bPin, 255);
}
void TriangleSet::goBlue() {
	writer.write(_rPin, 255);
	writer.write(_gPin, 255);
	writer.write(_bPin, 0);
}
void TriangleSet::goGreen() {
	writer.write(_rPin, 255);
	writer.write(_gPin, 0);
	writer.write(_bPin, 255);
}
void TriangleSet::goFull() {
	writer.write(_rPin, 255);
	writer.write(_gPin, 255);
	writer.write(_bPin, 255);
}
void TriangleSet::goZero() {
	writer.write(_rPin, 0);
	writer.write(_gPin, 0);
	writer.write(_bPin, 0);
}

void TriangleSet::manualWrite(int red, int green, int blue){
	writer.write(_rPin, red);
	writer.write(_gPin, green);
	writer.write(_bPin, blue);
}

