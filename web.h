#ifndef WEB_H
#define WEB_H

#include "Arduino.h"
#include <WiFi.h>
#include <WebServer.h>
#include <index.h>

/* cac bien luu cho webserver*/
extern const char* ssid;
extern const char* pass;

extern String real_time;
extern String morning_time;
extern String noon_time;
extern String evening_time;

//giao dien chinh
void homePage();

// Gửi thời gian thật và thời gian hẹn (JSON)
void handleTime();
void handleSaveRealTime();
void handleSaveSchedule();
void webInit();
#endif
