#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
#include "screen.h"
#include "clock.h"

//8:19:12:26:9:2015:0:13.4:82:24.0:40
void setup() {
    Serial.begin(9600);
    initialize();
}

void loop() {
  
  clockContinue();
  draw();
}
