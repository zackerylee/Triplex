#include "TriplexWriter.h"

TriplexWriter::TriplexWriter(uint8_t shieldAddress) {
  address = shieldAddress;
}

void TriplexWriter::setup() {
  Serial.print("setup triplexwriter ");
  Serial.println(address);
  pwm = Adafruit_PWMServoDriver(address);
  pwm.begin();
  // I think to replicate the frequency the arduino was writing to the LED amp, this should be 500?
  pwm.setPWMFreq(500);
}

void TriplexWriter::write(int pin, int value) {
  pwm.setPWM(pin, 0, map(value, 0, 255, 4095, 0));
}
