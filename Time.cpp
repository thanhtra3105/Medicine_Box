#include "Time.h"

hw_timer_t * timer = NULL;
extern Time myTime;
extern bool activeAlarm;  // khai báo extern
extern volatile bool activeFlag;
extern uint8_t drawer[3];
extern uint8_t currentDrawer;
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

  // if(myTime.hour == myTime.hourAlarm.morning && myTime.minute == myTime.minuteAlarm.morning || 
  //    myTime.hour == myTime.hourAlarm.afternoon && myTime.minute == myTime.minuteAlarm.afternoon ||
  //    myTime.hour == myTime.hourAlarm.evening && myTime.minute == myTime.minuteAlarm.evening) 
  // {
  //     // chua nhan thuoc
  //   activeAlarm = true;
  //   // activeFlag = true;
  // } 
  // else 
  // {
  //   if(activeFlag == false)
  //       activeAlarm = false;
  // }

  if (myTime.hour == myTime.hourAlarm.morning && myTime.minute == myTime.minuteAlarm.morning) {
    activeAlarm = true;
    currentDrawer = drawer[0]; 
  }
  else if (myTime.hour == myTime.hourAlarm.afternoon && myTime.minute == myTime.minuteAlarm.afternoon) {
    activeAlarm = true;
    currentDrawer = drawer[1]; 
  }
  else if (myTime.hour == myTime.hourAlarm.evening && myTime.minute == myTime.minuteAlarm.evening) {
    activeAlarm = true;
    currentDrawer = drawer[2]; 
  }
  else {
    if (activeFlag == false)
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
