#include <SPI.h>
#include "S25FL208K.h"

S25FL208K *spiFlash;

void setup(){
  Serial.begin(115200);
  // if this is run before setup, then doesn't work.
  // other option is to have an init function.
  //spiFlash = new S25FL208K(4);
  Serial.println("Setup complete.");

  //Serial.println(spiFlash->readStatus(),BIN);
  //spiFlash->writeEnable();
  //Serial.println(spiFlash->readStatus(),BIN);

  SPI.begin();
  int csPin = 4;
  pinMode(csPin, OUTPUT);
  digitalWrite(csPin, 1);

  uint8_t res = 0;
  digitalWrite(csPin, 0);
  SPI.transfer(0x05);
  res = SPI.transfer(0);
  digitalWrite(csPin, 1);

  Serial.println(res,BIN);

  digitalWrite(csPin, 0);
  SPI.transfer(0x06);
  digitalWrite(csPin, 1);

  digitalWrite(csPin, 0);
  SPI.transfer(0x05);
  res = SPI.transfer(0);
  digitalWrite(csPin, 1);

  Serial.println(res,BIN);

  digitalWrite(csPin, 0);
  SPI.transfer(0x04);
  digitalWrite(csPin, 1);

  digitalWrite(csPin, 0);
  SPI.transfer(0x05);
  res = SPI.transfer(0);
  digitalWrite(csPin, 1);

  Serial.println(res,BIN);




}

void loop(){

}
