#include "TriplexWriter.h"

TriplexWriter::TriplexWriter(uint8_t shieldAddress, int pPower) {
  address = shieldAddress;
  power = pPower;
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
  int mapVal = map(value, 0, 255, 4095, power);
  pwm.setPWM(pin, 0, mapVal);
}
