#include <math.h>

boolean DigitOn = LOW;
boolean DigitOff = HIGH;
boolean SegOn = HIGH;
boolean SegOff = LOW;
boolean backlight = true;
int DigitPins[] = {2, 3, 4, 5};
int SegmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

//looks terrible, but I didn't find a way to copy Arrays or merge them from parts
//N is for numbers and NxP is a number with a decimal point behind
int BLANK[] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int N0[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int N0P[]   = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH};
int N1[]    = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N1P[]   = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
int N2[]    = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};
int N2P[]   = {HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH};
int N3[]    = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, LOW};
int N3P[]   = {HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH, HIGH};
int N4[]    = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, LOW};
int N4P[]   = {LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH, HIGH};
int N5[]    = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int N5P[]   = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH};
int N6[]    = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N6P[]   = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int N7[]    = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int N7P[]   = {HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW, HIGH};
int N8[]    = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int N8P[]   = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int N9[]    = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int N9P[]   = {HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH};
int MIN[]   = {LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW};
//The letters K, M, N, T, V, W, Z are off limits with a 7 segment display
//Some letters like D, G, Q are hard to recognize, as D is like O and G like 6
int A[] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int B[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int C[] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW};
int D[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int E[] = {HIGH, LOW, LOW, HIGH, HIGH, HIGH, HIGH, LOW};
int F[] = {HIGH, LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW};
int G[] = {HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW};
int H[] = {LOW, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int I[] = {LOW, HIGH, HIGH, LOW, LOW, LOW, LOW, LOW};
int J[] = {LOW, HIGH, HIGH, HIGH, HIGH, LOW, LOW, LOW};
int L[] = {LOW, LOW, LOW, HIGH, HIGH, HIGH, LOW, LOW};
int O[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int P[] = {HIGH, HIGH, LOW, LOW, HIGH, HIGH, HIGH, LOW};
int Q[] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, HIGH};
int R[] = {HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH, LOW};
int S[] = {HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
int U[] = {LOW, HIGH, HIGH, HIGH, HIGH, HIGH, LOW, LOW};
int Y[] = {LOW, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, LOW};
//Array of pointers for the 4 digits
int* lights[4];

int calculateDigits(double value) {
  int digits = 0;
  if (round(value) <= -10) {
    digits = 3;
  } else if (round(value) < 0) {
    digits = 2;
  } else if (round(value) < 10) {
    digits = 1;
  } else if (round(value) < 100) {
    digits = 2;
  } else if (round(value) >= 100) {
    digits = 3;
  }
  return digits;
}

void initLCD() {
  lcd.begin(16, 2);
  if(backlight) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }
  lcd.setCursor(10, 0);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(15, 0);
  lcd.print("%");
  lcd.setCursor(10, 1);
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(15, 1);
  lcd.print("%");
}

void printSync(boolean error) {
  lcd.setCursor(0, 1);
  lcd.print("        ");
  lcd.setCursor(0, 1);
  if (!error) {
    lcd.print("Sync OK");
  } else {
    lcd.print("Sync ERR");
  }
}

void initialize() {
  lcd.clear();
  initLCD();
  for (byte digit = 0; digit < 4; digit++) {
    pinMode(DigitPins[digit], OUTPUT);
  }
  for (byte seg = 0; seg < 8; seg++) {
    pinMode(SegmentPins[seg], OUTPUT);
  }
  //initialize display with 1.234
  lights[0] = N0;
  lights[1] = N0P;
  lights[2] = N0;
  lights[3] = N0;
}

void updateDigits(int digit[4]) {
  for (int i = 0; i < 4; i++) {
    if (i != 1) {
      switch (digit[i]) {
        case 0: lights[i] = N0; break;
        case 1: lights[i] = N1; break;
        case 2: lights[i] = N2; break;
        case 3: lights[i] = N3; break;
        case 4: lights[i] = N4; break;
        case 5: lights[i] = N5; break;
        case 6: lights[i] = N6; break;
        case 7: lights[i] = N7; break;
        case 8: lights[i] = N8; break;
        case 9: lights[i] = N9; break;
        default: lights[i] = N0;
      }
    } else {
      switch (digit[i]) {
        case 0: lights[i] = N0P; break;
        case 1: lights[i] = N1P; break;
        case 2: lights[i] = N2P; break;
        case 3: lights[i] = N3P; break;
        case 4: lights[i] = N4P; break;
        case 5: lights[i] = N5P; break;
        case 6: lights[i] = N6P; break;
        case 7: lights[i] = N7P; break;
        case 8: lights[i] = N8P; break;
        case 9: lights[i] = N9P; break;
        default: lights[i] = N0P;
      }
    }
  }
}

void draw() {
  //This part of the code is from the library SevSeg by Dean Reading
  for (byte seg = 0; seg < 8; seg++) {
    //Turn the relevant segment on
    digitalWrite(SegmentPins[seg], SegOn);

    //For each digit, turn relevant digits on
    for (byte digit = 0; digit < 4; digit++) {
      if (lights[digit][seg] == 1) {
        digitalWrite(DigitPins[digit], DigitOn);
      }
      //delay(200); //Uncomment this to see it in slow motion
    }
    //Turn all digits off
    for (byte digit = 0; digit < 4; digit++) {
      digitalWrite(DigitPins[digit], DigitOff);
    }

    //Turn the relevant segment off
    digitalWrite(SegmentPins[seg], SegOff);
  } //end of for
}

void changeBacklightState() {
  if(backlight) {
    backlight = false;
    lcd.noBacklight();
  } else {
    backlight = true;
    lcd.backlight();
  }
}

void updateWeather(double temp, int humidity, double localTemp, int localHum) {
  int tempDigits = calculateDigits(temp);
  int humDigits = calculateDigits((double) humidity);
  int localTempDigits = calculateDigits(localTemp);
  int localHumDigits = calculateDigits((double) localHum);
  lcd.setCursor(10 - tempDigits, 0);
  lcd.print(temp, 0);
  lcd.setCursor(15 - humDigits, 0);
  lcd.print(humidity);
  lcd.setCursor(10 - localTempDigits, 1);
  lcd.print(localTemp, 0);
  lcd.setCursor(15 - localHumDigits, 1);
  lcd.print(localHum);
}

