#include <SPI.h>
#include "S25FL208K.h"

S25FL208K *spiFlash;

uint32_t testAddr = 0x000008;

void setup(){
  Serial.begin(115200);
  // if this is run before setup, then doesn't work.
  // other option is to have an init function.
  spiFlash = new S25FL208K(4);
  Serial.println("Setup complete.");

  String test = "Hello world";

  uint8_t* dataToStore = new uint8_t[test.length()];
  for(int i = 0; i<test.length(); i++){
    dataToStore[i] = uint8_t(test[i]);
  }

  unsigned long timeWrite = millis();
  spiFlash->storeData(testAddr, test.length(), dataToStore);

  while(spiFlash->getWIP()){
    Serial.print(".");
  }

  Serial.print("\nTime taken to write:");
  Serial.println(millis() - timeWrite);

  uint8_t* dataToRead = new uint8_t[20];
  spiFlash->readData(0, 20, dataToRead);
  for(int i = 0; i<20; i++){
    Serial.print((char)dataToRead[i]);
  }
}

void loop(){

}
