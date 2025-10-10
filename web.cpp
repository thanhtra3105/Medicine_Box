#include "web.h"
#include <Time.h>
extern WebServer server;
extern Time myTime;

extern bool activeAlarm;  // khai báo extern
extern uint8_t status;
extern uint8_t drawer;

const char* ssid = "Son Tra";
const char* pass = "L02012001";

String real_time = "00:00";
String morning_time = "07:00";
String noon_time = "12:00";
String evening_time = "19:00";

void homePage() {
  server.send_P(200, "text/html", MAIN_page);
}

void handleTime() {
  char buff[200];
  const char* statusText;
  if(status == 0)
  {
    statusText = "Chưa tới giờ uống thuốc";
  }
  else if(status == 1)
  {
    statusText = "Đã đến giờ uống thuốc";
  }
  sprintf(buff,
    "{\"time\":\"%02d:%02d:%02d\","
    "\"morning\":\"%02d:%02d\","
    "\"noon\":\"%02d:%02d\","
    "\"evening\":\"%02d:%02d\","
    "\"status\":\"%s\"}",
    myTime.hour, myTime.minute, myTime.second,
    myTime.hourAlarm.morning, myTime.minuteAlarm.morning,
    myTime.hourAlarm.afternoon, myTime.minuteAlarm.afternoon,
    myTime.hourAlarm.evening, myTime.minuteAlarm.evening, 
    statusText
  );
  server.send(200, "application/json", buff);
}

// Nhận dữ liệu khi người dùng nhấn “Lưu”
void handleSaveRealTime() {
  if (server.hasArg("real")) real_time = server.arg("real");
  
  String msg = "Đã lưu thời gian thực: " + real_time;
  // Cập nhật giờ thực tế
  int h,m;
  sscanf(real_time.c_str(), "%2d:%2d", &h, &m);
  myTime.hour = h;
  myTime.minute = m;
  myTime.second = 0;
  // Gửi phản hồi về trình duyệt  
  server.send(200, "text/plain", msg);
}

void handleSaveSchedule() {
  if (server.hasArg("morning")) morning_time = server.arg("morning");
  if (server.hasArg("noon")) noon_time = server.arg("noon");
  if (server.hasArg("evening")) evening_time = server.arg("evening");
  if(server.hasArg("drawer")) drawer = server.arg("drawer").toInt();
  String msg = "Đã lưu giờ hẹn: Sáng " + morning_time + ", Trưa " + noon_time + ", Tối " + evening_time;
  // Cập nhật giờ thực tế
  int h,m;
  // Cập nhật giờ hẹn
  sscanf(morning_time.c_str(), "%d:%d", &h, &m);
  myTime.hourAlarm.morning = h;
  myTime.minuteAlarm.morning = m;

  sscanf(noon_time.c_str(), "%d:%d", &h, &m);
  myTime.hourAlarm.afternoon = h;
  myTime.minuteAlarm.afternoon = m;

  sscanf(evening_time.c_str(), "%d:%d", &h, &m);
  myTime.hourAlarm.evening = h;
  myTime.minuteAlarm.evening = m;
  // Gửi phản hồi về trình duyệt  
  server.send(200, "text/plain", msg);
}


void webInit() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  server.on("/", homePage);
  server.on("/time", handleTime);
  server.on("/saveSchedule", handleSaveSchedule);
  server.on("/saveReal", handleSaveRealTime);
  server.begin();
  Serial.println(WiFi.localIP());
  myTime.hour = 23;
  myTime.minute = 39;
  myTime.second = 50;
  myTime.hourAlarm.morning = 23;
  myTime.minuteAlarm.morning = 40;

}
