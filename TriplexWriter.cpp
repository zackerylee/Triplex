#include "TriplexWriter.h"

TriplexWriter::TriplexWriter(uint8_t shieldAddress) {
	address = shieldAddress;
	if (address != 0x0) {
		mode = SHIELD_MODE;
	}
	else {
		mode = SIMPLE_MODE;
	}	
  if (mode == SHIELD_MODE) {
	 	pwm = Adafruit_PWMServoDriver(address);
   pwm.begin();
   // I think to replicate the frequency the arduino was writing to the LED amp, this should be 500?
   pwm.setPWMFreq(500);

   // these are from the pwmtest.ino in the example package, not sure if we need them

   // save I2C bitrate
   uint8_t twbrbackup = TWBR;
   // must be changed after calling Wire.begin() (inside pwm.begin())
   TWBR = 12; // upgrade to 400KHz!

    
	} 	
}

void TriplexWriter::write(int pin, int value) {
	if (mode == SHIELD_MODE) {
		// this is my best guess what this is going to look like
    
		pwm.setPWM(pin, 0, map(value, 0, 255, 4096, 0));
    // or should it really be?
    //pwm.setPWM(pin, 0, map(value, 0, 255, 0, 4096));
	}
	else {
		// we generally count 255 as being "on" but I think that is backwards, 
		//  map the other way
		analogWrite(pin, map(value, 0, 255, 255, 0));
	}
}
