#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7);
#include "screen.h"
#include "clock.h"
const int MIN_RAW_DATA_LENGTH = 28;
const int MAX_RAW_DATA_LENGTH = 37;
char raw[MAX_RAW_DATA_LENGTH] = {};
double values[11] = {};

//8:19:12:26:9:2015:0:13.4:82:24.0:40-
//8:3:2:1:1:2015:0:2.0:5:1.0:5-
void setup() {
    Serial.begin(9600);
    initialize();
}

void loop() {
  memset(&values, NULL, sizeof(values));
  if(Serial.available() > 0) {
    byte readedBytes = Serial.readBytesUntil('-' ,raw, MAX_RAW_DATA_LENGTH);
    if(readedBytes >= MIN_RAW_DATA_LENGTH && readedBytes <= MAX_RAW_DATA_LENGTH) {
      //Si entra aquí es que ha leido correctamente los bytes
      Serial.print("Se han leido : ");
      Serial.println(readedBytes, DEC);
      //Hacemos un split en el char[] y guardamos los valores
      char *pointer = strtok(raw, ":");
      int counter = 0;
      while(pointer != NULL && counter <= sizeof(values)) {
        values[counter] = strtod(pointer, NULL);
        Serial.print("Introduciendo el valor en el array: ");
        Serial.println(values[counter]);
        pointer = strtok(NULL, ":");
        counter++;
      }
      //Comprobamos si ha habido errores y actualizamos los datos en pantalla.
      if(values[6] != 1) {
        updateValues();
      } else {
        printSync(true);
        Serial.print("Se ha producido un error al recibir los datos: ");
        Serial.println(values[6]);
      }
    }
    memset(&raw, NULL, sizeof(raw));
  }
  clockContinue();
  draw();
}

void updateValues() {
  int hour = values[0];
  int min = values[1];
  int sec = values[2];
  int day = values[3];
  int month = values[4];
  int year = values[5];
  double temp = values[7];
  int hum = values[8];
  double localTemp = values[9];
  int localHum = values[10];
  updateTime(hour, min, sec, day, month, year);
  updateWeather(temp, hum, localTemp, localHum);  
  printSync(false);
}

