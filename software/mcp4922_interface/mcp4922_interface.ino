#include <SPI.h>

// PINS
uint8_t pinChipSelect_1 = 10;
uint8_t pinChipSelect_2 = 9;
uint8_t pinLDAC = 7;

// 0 ==> chipselect_1 = 1, chipselect_2 = 0 else opposite
uint8_t chipSelect;

SPISettings _spiSettings;

void _beginTransmission() {
  SPI.beginTransaction(_spiSettings);
  digitalWrite(pinLDAC, 0);
  if(!chipSelect) {
    digitalWrite(pinChipSelect_1, 0);
  } else {
    digitalWrite(pinChipSelect_2, 0);
  }
}

void _endTransmission() {
  if(!chipSelect) {
    digitalWrite(pinChipSelect_1, 1);
  } else {
    digitalWrite(pinChipSelect_2, 1);
  }
  digitalWrite(pinLDAC, 1);
  SPI.endTransaction();
}

void mcp16bitOut(int value) {
  chipSelect = 0;
  uint8_t odd = 0;
  byte firstByte = (value & 0xFF00) >> 8;
  byte secondByte = value & 0xFF;

  _beginTransmission();
  SPI.transfer(firstByte);
  SPI.transfer(secondByte);
  _endTransmission();
}

void mcpAnalogOut(int value, int selector) {
  uint8_t odd;
  if(selector == 0) {
    chipSelect = 0;
    odd = 0;
  } else if (selector == 1) {
    chipSelect = 0;
    odd = 1;
  } else if (selector == 2) {
    chipSelect = 1;
    odd = 0;
  } else {
    chipSelect = 1;
    odd = 1;
  }
  byte configBits = odd << 3 | 1 << 2 | 1 << 1 | 1;

  byte firstByte = configBits << 4 | (value & 0xF00) >> 8;
  byte secondByte = value & 0xFF;

  _beginTransmission();
  SPI.transfer(firstByte);
  SPI.transfer(secondByte);
  _endTransmission();
}

void setup() {
  chipSelect = 0;
  // set chipSelect pins to output
  pinMode(pinChipSelect_1, OUTPUT);
  pinMode(pinChipSelect_2, OUTPUT);
  pinMode(pinLDAC, OUTPUT);

  // set a default starting value
  digitalWrite(pinChipSelect_1, 1);
  digitalWrite(pinChipSelect_2, 1);
  digitalWrite(pinLDAC, 1);

  _spiSettings = SPISettings(2000, MSBFIRST, SPI_MODE0);

  SPI.begin();
}

void loop() {
//  for(int i = 0; i < 65536; i++) {
    mcpAnalogOut(4095, 2);
    delayMicroseconds(10000);
//  }
/*  mcpAnalogOut(0, 0);
  delayMicroseconds(100);
  for(int i = 0; i < 4096; i++) {
    mcpAnalogOut(i, 1);
    delayMicroseconds(100);
  }
  mcpAnalogOut(0, 1);
  delayMicroseconds(100);
  for(int i = 0; i < 4096; i++) {
    mcpAnalogOut(i, 2);
    delayMicroseconds(100);
  }
  mcpAnalogOut(0, 2);
  delayMicroseconds(100);
  for(int i = 0; i < 4096; i++) {
    mcpAnalogOut(i, 3);
    delayMicroseconds(100);
  }
  mcpAnalogOut(0, 3);
  delayMicroseconds(100);*/
}
