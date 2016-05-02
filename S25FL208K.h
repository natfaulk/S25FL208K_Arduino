#ifndef S25FL208K_h
#define S25FL208K_h

#include <arduino.h>

const uint8_t WRITE_ENABLE = 0x06;
const uint8_t WRITE_DISABLE = 0x04;
const uint8_t READ_STATUS_REG = 0x05;
const uint8_t WRITE_STATUS_REG = 0x01;
const uint8_t READ_DATA = 0x03;
const uint8_t FAST_READ = 0x0B;
const uint8_t FAST_READ_DUAL_OUTPUT = 0x3B;
const uint8_t PAGE_PROGRAM = 0x02;
const uint8_t BLOCK_ERASE = 0xD8; // 64kb
const uint8_t SECTOR_ERASE = 0x20; // 4kb
const uint8_t CHIP_ERASE = 0xC7; // or 0x60;
const uint8_t POWER_DOWN = 0xB9;
const uint8_t RELEASE_POWER_DOWN = 0xAB;
const uint8_t DEV_ID = 0x90;
const uint8_t JEDEC_ID = 0x9F;
const uint8_t DUMMY_VALUE = 0x00;
const uint8_t WIP_MASK = 0x01;

class S25FL208K{
public:
  S25FL208K(uint8_t csPin);
  uint8_t readStatus();
  bool readData(uint32_t address, uint32_t numBytes, uint8_t* &result);
  void writeEnable(void);
  void writeDisable(void);
  bool getWIP(void);
  bool chipErase(void);
  bool sectorErase(uint32_t address);
  bool blockErase(uint32_t address);
  // address is 24 bytes, however no uint24_t data type
  // up to 255 bytes (chip supports up to 256 at once but want to use a uint8_t)
  bool storeData(uint32_t address, uint8_t numBytes, uint8_t* &data);
private:
  // returns dynamic memory
  // therefore needs a delete[] call on the pointer when done
  uint8_t* sendCommand(uint8_t command, uint8_t bytesToRead = 0);
  uint8_t mCsPin;
};

#endif
