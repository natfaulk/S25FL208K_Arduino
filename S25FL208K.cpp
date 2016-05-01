#include "S25FL208K.h"
#include <SPI.h>

S25FL208K::S25FL208K(uint8_t csPin){
  SPI.begin();
  mCsPin = csPin;
  pinMode(mCsPin, OUTPUT);
  digitalWrite(mCsPin, 1); // active low, start disabled
}

uint8_t S25FL208K::sendCommand(uint8_t command){
  uint8_t result = 0;
  digitalWrite(mCsPin, 0);
  result = SPI.transfer(command);
  digitalWrite(mCsPin, 1);
  return result;
}

uint8_t S25FL208K::readStatus(){
  sendCommand(READ_STATUS_REG);
  return sendCommand(DUMMY_VALUE);
}

uint8_t S25FL208K::readData(uint32_t address, uint32_t numBytes){
  sendCommand(READ_DATA);
  // send 24bit address, continuosly read
  return sendCommand(DUMMY_VALUE);// dont use. is a placeholder!
}

void S25FL208K::writeEnable(void){
  sendCommand(WRITE_ENABLE);
}
