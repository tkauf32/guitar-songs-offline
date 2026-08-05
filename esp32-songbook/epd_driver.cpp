#include "epd_driver.h"

namespace {

void writeBus(uint8_t data) {
  digitalWrite(PIN_EPD_CS, LOW);
  for (uint8_t i = 0; i < 8; i++) {
    digitalWrite(PIN_EPD_SCK, LOW);
    digitalWrite(PIN_EPD_MOSI, (data & 0x80) ? HIGH : LOW);
    digitalWrite(PIN_EPD_SCK, HIGH);
    data <<= 1;
  }
  digitalWrite(PIN_EPD_CS, HIGH);
}

void writeCommand(uint8_t command) {
  digitalWrite(PIN_EPD_DC, LOW);
  writeBus(command);
  digitalWrite(PIN_EPD_DC, HIGH);
}

void writeData(uint8_t data) {
  digitalWrite(PIN_EPD_DC, HIGH);
  writeBus(data);
}

void waitBusy() {
  while (digitalRead(PIN_EPD_BUSY) != LOW) {
    delayMicroseconds(100);
  }
  delayMicroseconds(100);
}

void resetPanel() {
  delay(100);
  digitalWrite(PIN_EPD_RES, HIGH);
  delay(10);
  digitalWrite(PIN_EPD_RES, LOW);
  delay(10);
  digitalWrite(PIN_EPD_RES, HIGH);
  delay(10);
  waitBusy();
  writeCommand(0x12);
  waitBusy();
}

}  // namespace

void epdInit() {
  pinMode(PIN_EPD_SCK, OUTPUT);
  pinMode(PIN_EPD_MOSI, OUTPUT);
  pinMode(PIN_EPD_RES, OUTPUT);
  pinMode(PIN_EPD_DC, OUTPUT);
  pinMode(PIN_EPD_CS, OUTPUT);
  pinMode(PIN_EPD_BUSY, INPUT);

  resetPanel();

  writeCommand(0x01);
  writeData(0xF9);
  writeData(0x00);
  writeData(0x00);

  writeCommand(0x11);
  writeData(0x03);

  writeCommand(0x44);
  writeData(0x00);
  writeData(0x0F);

  writeCommand(0x45);
  writeData(0x00);
  writeData(0x00);
  writeData(0xF9);
  writeData(0x00);

  writeCommand(0x3C);
  writeData(0x01);
  waitBusy();

  writeCommand(0x18);
  writeData(0x80);

  writeCommand(0x4E);
  writeData(0x00);
  writeCommand(0x4F);
  writeData(0x00);
  writeData(0x00);

  waitBusy();
}

void epdDisplayImage(const uint8_t* image) {
  writeCommand(0x3C);
  writeData(0x01);

  writeCommand(0x24);
  for (int i = 0; i < EPD_BUFFER_SIZE; i++) {
    writeData(static_cast<uint8_t>(~image[i]));
  }

  writeCommand(0x22);
  writeData(0xF4);
  writeCommand(0x20);
  waitBusy();
}

void epdSleep() {
  writeCommand(0x10);
  writeData(0x01);

  writeCommand(0x3C);
  writeData(0x01);
  delay(20);
}
