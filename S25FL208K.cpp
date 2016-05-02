#include "S25FL208K.h"
#include <SPI.h>

S25FL208K::S25FL208K(uint8_t csPin){
  SPI.begin();
  mCsPin = csPin;
  pinMode(mCsPin, OUTPUT);
  digitalWrite(mCsPin, 1); // active low, start disabled
}

// returns dynamic memory
// therefore needs a delete[] call on the pointer when done
uint8_t* S25FL208K::sendCommand(uint8_t command, uint8_t bytesToRead){
  uint8_t* result = NULL;
  digitalWrite(mCsPin, 0);
  SPI.transfer(command);
  if (bytesToRead > 0){
    result = new uint8_t[bytesToRead];
    for (int i = 0; i<bytesToRead; i++){
      result[i] = SPI.transfer(DUMMY_VALUE);
    }
  }
  digitalWrite(mCsPin, 1);
  return result;
}

uint8_t S25FL208K::readStatus(){
  uint8_t* result = NULL;
  uint8_t output = 0;
  result = sendCommand(READ_STATUS_REG, 1);
  output = result[0];
  delete[] result;
  return output;
}

void S25FL208K::writeEnable(void){
  sendCommand(WRITE_ENABLE);
}

void S25FL208K::writeDisable(void){
  sendCommand(WRITE_DISABLE);
}

bool S25FL208K::getWIP(void){
  return (this->readStatus() & WIP_MASK);
}

bool S25FL208K::readData(uint32_t address, uint32_t numBytes, uint8_t* &result){
  // check WIP bit
  if (this->getWIP()){
    return false;
  }

  digitalWrite(mCsPin, 0);
  // transfer the address as 3 bytes
  SPI.transfer(READ_DATA);
  SPI.transfer(uint8_t(0xFF & (address>>16)));
  SPI.transfer(uint8_t(0xFF & (address>>8)));
  SPI.transfer(uint8_t(0xFF & address));

  // read the data into result
  for(int i = 0; i<numBytes; i++){
    result[i] = SPI.transfer(DUMMY_VALUE);
  }
  // end transfer
  digitalWrite(mCsPin, 1);
  return true;
}

bool S25FL208K::storeData(uint32_t address, uint8_t numBytes, uint8_t* &data){
  // check WIP bit
  if (this->getWIP()){
    return false;
  }

  // check page erased
  bool allOnes = true;
  uint8_t tempResult = new uint8_t[numBytes];
  this->readData(address, numBytes, tempResult);
  for (int i = 0; i<numBytes; i++){
    if (tempResult[i]!=0xFF){
      allOnes = false;
    }
  }
  delete[] tempResult;

  if (!allOnes){
    return false;
  }

  // set WRITE_ENABLE
  this->writeEnable();

  digitalWrite(mCsPin, 0);
  // send address
  SPI.transfer(PAGE_PROGRAM);
  SPI.transfer(uint8_t(0xFF & (address>>16)));
  SPI.transfer(uint8_t(0xFF & (address>>8)));
  SPI.transfer(uint8_t(0xFF & address));
  //send data
  for(int i = 0; i<numBytes; i++){
    SPI.transfer(data[i]);
  }

  digitalWrite(mCsPin, 1);

  return true;
}
