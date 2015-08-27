
#ifndef TriplexWriter_H
#define TriplexWriter_H

#include "Arduino.h"
#include <Adafruit_PWMServoDriver.h>

const int SIMPLE_MODE = 1;
const int SHIELD_MODE = 2;

class TriplexWriter {
public: 
	TriplexWriter(uint8_t shieldAddress = 0x0, int pPower = 0);
  void setup();
	void write(int pin, int value);

private:
	int mode;
  int power;
	uint8_t address;
	Adafruit_PWMServoDriver pwm;
};

#endif
