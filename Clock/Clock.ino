#include <RTClib.h>
#include <Wire.h>
#define MINUTE_PINS_COUNT 6
#define HOUR_PINS_COUNT 4

bool _isEnabled = false;
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
  if (! rtc.begin()) 
  {
    Serial.println("RTC Not found");
  }
  else 
  {
    _isEnabled = true;
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  if(!_isEnabled)
  {
    return;
  }

  DateTime _rtc = rtc.now();
  int minutes = _rtc.minute();
  int hours = _rtc.hour();
  
  // Corresponding to on/off pins to LEDs of minutes (LSB at index 0)
  bool minute_pins[MINUTE_PINS_COUNT];
  for(int i = 0; i < MINUTE_PINS_COUNT; i++)
  {
    minute_pins[i] = minutes % 2;
    minutes /= 2;
  }

  // Corresponding to on/off pins to LED of AM/PM
  bool isPM = hours >= 12;
  
  // Corresponding to on/off pins to LEDs of hours (LSB at index 0)
  bool hour_pins[HOUR_PINS_COUNT];
  for(int i = 0; i < HOUR_PINS_COUNT; i++)
  {
    hour_pins[i] = minutes % 2;
    hours /= 2;
  }
  Serial.println(minute_pins[0]);
  delay(1000);
  
}
