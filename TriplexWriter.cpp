#include "TriplexWriter.h"

TriplexWriter::TriplexWriter(uint8_t shieldAddress) {
	address = shieldAddress;
	if (address != 0x0) {
		mode = SHIELD_MODE;
	}
	else {
		mode = SIMPLE_MODE;
	}	
	// if (mode == SHIELD_MODE) {
	// 	driver = Adafruit_PMWServoDriver(address);
	// } 	
}

void TriplexWriter::write(int pin, int value) {
	if (mode == SHIELD_MODE) {
		// this is my best guess what this is going to look like
		// driver.write(pin, map(value, 0, 255, 0, 1024));
	}
	else {
		// we generally count 255 as being "on" but I think that is backwards, 
		//  map the other way
		analogWrite(pin, map(value, 0, 255, 255, 0));
	}
}
