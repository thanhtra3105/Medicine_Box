#ifndef TIME_H
#define TIME_H

#include "Arduino.h"

class Time {
  public:
  volatile uint8_t second = 0;
  volatile uint8_t minute;
  volatile uint8_t hour;

  struct AlarmField{ 
    uint8_t morning = 0;
    uint8_t afternoon = 0;
    uint8_t evening = 0;
  } ;

  AlarmField minuteAlarm;
  AlarmField hourAlarm;

};

void timerInit();
#endif
