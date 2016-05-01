#include <SPI.h>
#include "S25FL208K.h"

S25FL208K *spiFlash;

void setup(){
  Serial.begin(115200);
  // if this is run before setup, then doesn't work.
  // other option is to have an init function.
  spiFlash = new S25FL208K(4);
  Serial.println("Setup complete.");

  Serial.println(spiFlash->readStatus(),BIN);
  spiFlash->writeEnable();
  Serial.println(spiFlash->readStatus(),BIN);
}

void loop(){

}
