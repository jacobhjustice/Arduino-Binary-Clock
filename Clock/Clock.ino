#include <RTClib.h>
#include <Wire.h>
const unsigned int MINUTE_PINS_COUNT = 6;
const unsigned int HOUR_PINS_COUNT = 4;
const unsigned int MINUTE_PIN_START = 2;
const unsigned int HOUR_PIN_START= 8;
const unsigned int PM_PIN = 13;
const unsigned int MAX_PIN = 13;

bool _isEnabled = false;
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Hello World!");
  if (! rtc.begin()) 
  {
    Serial.println("RTC Not found");
    while(1);
  }
  else if (rtc.lostPower()) 
  {
    Serial.println("RTC Lost power");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    _isEnabled = true;
  }
  else 
  {
    _isEnabled = true;
  }

}

void loop() {
  if(!_isEnabled)
  {
    return;
  }

  DateTime _rtc = rtc.now();
  Serial.println(_rtc.minute());
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
  if(hours > 11)
  {
    hours -= 11;
  }
  if(hours == 0)
  {
    hours = 12;
  }
  
  // Corresponding to on/off pins to LEDs of hours (LSB at index 0)
  bool hour_pins[HOUR_PINS_COUNT];
  for(int i = 0; i < HOUR_PINS_COUNT; i++)
  {
    hour_pins[i] = minutes % 2;
    hours /= 2;
  }
  //for(int i = 0; i < 6; i++)
 // {
  //    Serial.println(minute_pins[i]);

  //}
  clearPins();
  setPins(isPM, hour_pins, minute_pins);
    Serial.println("____");


  delay(1000);
  
}
void clearPins()
{
  for(int i = 1; i <= MAX_PIN; i++)
  {
    digitalWrite(i, LOW);
  }
}

void setPins(bool isPM, bool hour_pins[], bool minute_pins[]){
  for(int i = 0; i < MINUTE_PINS_COUNT; i++)
  {
    if(minute_pins[i])
    {
      digitalWrite(MINUTE_PIN_START+i, HIGH);
    }
  }
}
