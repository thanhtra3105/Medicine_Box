#include "Time.h"

hw_timer_t * timer = NULL;
extern Time myTime;
extern bool activeAlarm;  // khai báo extern


void IRAM_ATTR onTimer() {
  myTime.second++;
  if(myTime.second >= 60) {
    myTime.second = 0;
    myTime.minute++;
    if(myTime.minute >= 60) {
      myTime.minute = 0;
      myTime.hour++;
      if(myTime.hour >= 24) {
        myTime.hour = 0;
      }
    }
  }

  if(myTime.hour == myTime.hourAlarm.morning && myTime.minute == myTime.minuteAlarm.morning || 
     myTime.hour == myTime.hourAlarm.afternoon && myTime.minute == myTime.minuteAlarm.afternoon ||
     myTime.hour == myTime.hourAlarm.evening && myTime.minute == myTime.minuteAlarm.evening) 
  {
    activeAlarm = true;
  } 
  else 
  {
    activeAlarm = false;
  }
}

void timerInit()
{
  timer = timerBegin(0, 80, true);  // timer 0, prescaler 80, count up
  timerAttachInterrupt(timer, &onTimer, true);  // khai bao ham ngat
  timerAlarmWrite(timer, 1000000, true); // 1000000us = 1s, bat autoreload
  timerAlarmEnable(timer);  // enable timer
}