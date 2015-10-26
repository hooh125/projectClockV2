const String MONTH_NAME[12] = {"Ene", "Feb", "Mar", "Abr", "May", "Jun", "Jul", "Ago", "Sept", "Oct", "Nov", "Dic"};
const int HOUR_LIMIT = 23;
const int MIN_LIMIT = 59;
const int SEC_LIMIT = 59;
const int INTERVAL = 1000;
int hour = 0;
int min = 0;
int sec = 0;
int day = 0;
int month = 0;
int year = 0;

unsigned long previousMillis = 0;

void addSecond() {
  if(sec < SEC_LIMIT) {
            sec++;
        } else {
            sec = 0;
            if(min < MIN_LIMIT) {
                min++;
            } else {
                min = 0;
                if(hour < HOUR_LIMIT) {
                    hour++;
                } else {
                    hour = 0;
                }
            }
        }
}

void updateTime(int _hour, int _min, int _sec, int _day, int _month, int _year) {
  lcd.clear();
  initLCD();
  hour = _hour;
  min = _min;
  sec = _sec;
  day = _day;
  month = _month;
  year = _year;
  int dayLen = calculateDigits((double) day);
  lcd.setCursor(0,0);
  lcd.print(day);
  lcd.setCursor(1 + dayLen,0);
  lcd.print(MONTH_NAME[month]);
}

void clockContinue() {
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= INTERVAL) {
    //Si entra aquí es que ha pasado un segundo
    previousMillis = currentMillis;
    addSecond();
    int digits[4] = {hour / 10, hour % 10, min / 10, min % 10};
    updateDigits(digits);
  }
}
