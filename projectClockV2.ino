#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
#include "screen.h"
#include "clock.h"
const int RAW_DATA_LENGTH = 37;
char raw[RAW_DATA_LENGTH] = {};
char values[11] = {};

//8:19:12:26:9:2015:0:13.4:82:24.0:40
void setup() {
    Serial.begin(9600);
    initialize();
}

void loop() {
  memset(&values, NULL, sizeof(values));
  if(Serial.available() > 0) {
    byte readedBytes = Serial.readBytes(raw, RAW_DATA_LENGTH);
    if(readedBytes == RAW_DATA_LENGTH) {
      //Si entra aquí es que ha leido correctamente los bytes
    }
    memset(&raw, NULL, sizeof(raw));
  }
  clockContinue();
  draw();
}
