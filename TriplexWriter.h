#ifndef TriplexWriter_H
#define TriplexWriter_H

#include "Arduino.h"
//#include "Adafruit_PMWServoDriver.h"

const int SIMPLE_MODE = 1;
const int SHIELD_MODE = 2;

#define SHIELD_1 = 0x40;
#define SHIELD_2 = 0x41;

class TriplexWriter {
public: 
	TriplexWriter(uint8_t shieldAddress = 0x0);
	void write(int pin, int value);

private:
	int mode;
	uint8_t address;
	//Adafruit_PMWServoDriver driver;
};

#endif