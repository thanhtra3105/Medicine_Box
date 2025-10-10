// #include <Arduino.h>
// #include <Adafruit_SSD1306.h>
// #include <LiquidCrystal_I2C.h>

// #define LED1 8
// #define LED2 9
// #define BUZZER 7
// #define BUTTON 6
// #define SDA 4
// #define SCL 5
// #define sensor1 10
// bool button_state = false;
// unsigned long pre_time = 0;
// unsigned long time2 = 0;
// LiquidCrystal_I2C lcd(0x27, 20, 4);

// // Timer
// hw_timer_t * timer = NULL;
// volatile bool alarmActive = false;
// volatile bool blinkFlag = false;

// // Hàm ngắt Timer (500ms)
// void IRAM_ATTR onTimer() {
//   if (alarmActive) {
//     blinkFlag = !blinkFlag;  // đổi trạng thái LED/buzzer
//   }
// }

// void IRAM_ATTR handleInterrupt()
// {
//   button_state = !button_state;
  
// }

// void timer_init()
// {
//    // Khởi tạo timer: tick mỗi 500ms
//   timer = timerBegin(0, 80, true);               // 80 MHz / 80 = 1 MHz → 1 tick = 1 µs
//   timerAttachInterrupt(timer, &onTimer, true);
//   timerAlarmWrite(timer, 500000, true);          // 500000 µs = 500 ms
//   timerAlarmEnable(timer);
// }

// void setup()
// {
//   Serial.begin(9600);
//   Wire.begin(SDA, SCL);
//   lcd.init();
//   lcd.backlight();

//   pinMode(LED1, OUTPUT);
//   pinMode(LED2, OUTPUT);
//   pinMode(BUZZER, OUTPUT);
//   pinMode(BUTTON, INPUT_PULLUP);
//   pinMode(sensor1, INPUT);
//   attachInterrupt(digitalPinToInterrupt(BUTTON), handleInterrupt, FALLING);

//   timer_init();

//   lcd.setCursor(6,0);
//   lcd.print("TU THUOC");
//   lcd.setCursor(4,2);
//   lcd.print("Chua den gio!");
//   digitalWrite(BUZZER, 0);
//   digitalWrite(LED1, 1);
//   time2 = millis();
// }



// void loop()
// {
//   // tone(BUZZER, 500, 2000);
//   // delay(3000);
//   // if(millis() - time2 < 5000)
//   // {

//   //   digitalWrite(LED1, 1);
//   //   digitalWrite(LED2, 0);
//   //   tone(BUZZER, 500, 2000);
//   //   //noTone(BUZZER);
//   // }

//   // else if(millis() - time2 < 10000)
//   // {
//   //   digitalWrite(LED1, 0);
//   //   digitalWrite(LED2, 1);
//   //   tone(BUZZER, 500, 2000);
//   //   //noTone(BUZZER);
//   // }
//   // else if(millis() - time2 < 20000)
//   // {
//   //   time2 = millis();
//   // }

//   //Serial.println(button_state);
//   // Serial.println(digitalRead(sensor1));
//   // if(digitalRead(sensor1))
//   // {
//   //   digitalWrite(LED2, 0);
//   // }
//   // else
//   // {
//   //   digitalWrite(LED2, 1);
//   // }
//   // if(button_state)
//   // {
//   //   pre_time = millis();
//   //   lcd.setCursor(1,1);
//   //   lcd.print("Xac nhan lay thuoc");
//   //   lcd.setCursor(4,2);
//   //   lcd.print("             ");
//   //   digitalWrite(LED1, 0);
//   //   digitalWrite(LED2, 0);
//   //   delay(500);
//   //   button_state = !button_state;
//   // }
//   // else
//   // {
//   //   if(millis() - pre_time > 5000)
//   //   {
//   //     lcd.setCursor(0,1);
//   //     lcd.print("                     ");
//   //     lcd.setCursor(4,2);
//   //     lcd.print("Chua den gio!");
//   //     digitalWrite(LED1, 1);
//   //   }
//   // }

  
//   digitalWrite(LED1, blinkFlag);
// }

// #include "Arduino.h"
// #include <WiFi.h>
// #include <WebServer.h>
// #include <LiquidCrystal_I2C.h>
// #include <index.h>

// #define LED_PIN 8 
// #define BUZZER 7
// #define LED1 8
// #define LED2 9
// #define BUZZER 7
// #define BUTTON 6
// #define SDA 4
// #define SCL 5
// #define sensor1 10
// bool button_state = false;
// unsigned long pre_time = 0;
// unsigned long time2 = 0;

// volatile bool activeAlarm = false;
// const char* ssid = "Son Tra";
// const char* pass = "L02012001";
// uint8_t drawer = 1;
// uint8_t status = 0;  // trang thai da uong thuoc chua 0(chua toi gio), 1(den gio), 2(da uong thuoc)
// /* cac bien luu cho webserver*/
// String real_time = "00:00";
// String morning_time = "07:00";
// String noon_time = "12:00";
// String evening_time = "19:00";


// class Time {
//   public:
//   volatile uint8_t second = 0;
//   volatile uint8_t minute;
//   volatile uint8_t hour;

//   struct AlarmField{ 
//     uint8_t morning = 0;
//     uint8_t afternoon = 0;
//     uint8_t evening = 0;
//   } ;

//   AlarmField minuteAlarm;
//   AlarmField hourAlarm;

// };


// hw_timer_t * timer = NULL;
// Time myTime;
// LiquidCrystal_I2C lcd(0x27, 20, 4);
// WebServer server(80);


// void IRAM_ATTR onTimer() {
//   myTime.second++;
//   if(myTime.second >= 60) {
//     myTime.second = 0;
//     myTime.minute++;
//     if(myTime.minute >= 60) {
//       myTime.minute = 0;
//       myTime.hour++;
//       if(myTime.hour >= 24) {
//         myTime.hour = 0;
//       }
//     }
//   }

//   if(myTime.hour == myTime.hourAlarm.morning && myTime.minute == myTime.minuteAlarm.morning || 
//      myTime.hour == myTime.hourAlarm.afternoon && myTime.minute == myTime.minuteAlarm.afternoon ||
//      myTime.hour == myTime.hourAlarm.evening && myTime.minute == myTime.minuteAlarm.evening) 
//   {
//     activeAlarm = true;
//   } 
//   else 
//   {
//     activeAlarm = false;
//   }
// }

// //giao dien chinh
// void homePage() {
//   server.send_P(200, "text/html", MAIN_page);
// }

// // Gửi thời gian thật và thời gian hẹn (JSON)
// void handleTime() {
//   char buff[200];
//   const char* statusText;
//   if(status == 0)
//   {
//     statusText = "Chưa tới giờ uống thuốc";
//   }
//   else if(status == 1)
//   {
//     statusText = "Đã đến giờ uống thuốc";
//   }
//   sprintf(buff,
//     "{\"time\":\"%02d:%02d:%02d\","
//     "\"morning\":\"%02d:%02d\","
//     "\"noon\":\"%02d:%02d\","
//     "\"evening\":\"%02d:%02d\","
//     "\"status\":\"%s\"}",
//     myTime.hour, myTime.minute, myTime.second,
//     myTime.hourAlarm.morning, myTime.minuteAlarm.morning,
//     myTime.hourAlarm.afternoon, myTime.minuteAlarm.afternoon,
//     myTime.hourAlarm.evening, myTime.minuteAlarm.evening, 
//     statusText
//   );
//   server.send(200, "application/json", buff);
// }

// // Nhận dữ liệu khi người dùng nhấn “Lưu”
// void handleSaveRealTime() {
//   if (server.hasArg("real")) real_time = server.arg("real");
  
//   String msg = "Đã lưu thời gian thực: " + real_time;
//   // Cập nhật giờ thực tế
//   int h,m;
//   sscanf(real_time.c_str(), "%2d:%2d", &h, &m);
//   myTime.hour = h;
//   myTime.minute = m;
//   myTime.second = 0;
//   // Gửi phản hồi về trình duyệt  
//   server.send(200, "text/plain", msg);
// }

// void handleSaveSchedule() {
//   if (server.hasArg("morning")) morning_time = server.arg("morning");
//   if (server.hasArg("noon")) noon_time = server.arg("noon");
//   if (server.hasArg("evening")) evening_time = server.arg("evening");
//   if(server.hasArg("drawer")) drawer = server.arg("drawer").toInt();
//   String msg = "Đã lưu giờ hẹn: Sáng " + morning_time + ", Trưa " + noon_time + ", Tối " + evening_time;
//   // Cập nhật giờ thực tế
//   int h,m;
//   // Cập nhật giờ hẹn
//   sscanf(morning_time.c_str(), "%d:%d", &h, &m);
//   myTime.hourAlarm.morning = h;
//   myTime.minuteAlarm.morning = m;

//   sscanf(noon_time.c_str(), "%d:%d", &h, &m);
//   myTime.hourAlarm.afternoon = h;
//   myTime.minuteAlarm.afternoon = m;

//   sscanf(evening_time.c_str(), "%d:%d", &h, &m);
//   myTime.hourAlarm.evening = h;
//   myTime.minuteAlarm.evening = m;
//   // Gửi phản hồi về trình duyệt  
//   server.send(200, "text/plain", msg);
// }


// void timer_init()
// {
//   timer = timerBegin(0, 80, true);  // timer 0, prescaler 80, count up
//   timerAttachInterrupt(timer, &onTimer, true);  // khai bao ham ngat
//   timerAlarmWrite(timer, 1000000, true); // 1000000us = 1s, bat autoreload
//   timerAlarmEnable(timer);  // enable timer
// }

// void setup() {
//   Serial.begin(9600);
//   pinMode(LED_PIN, OUTPUT);
//   pinMode(BUZZER, OUTPUT);
//   ledcSetup(0, 1000, 8);
//   ledcAttachPin(BUZZER, 0);
//   timer_init();
  
//   WiFi.mode(WIFI_STA);
//   WiFi.begin(ssid, pass);
//   Serial.print("Connecting to WiFi ..");
//   while (WiFi.status() != WL_CONNECTED) {
//     Serial.print('.');
//     delay(500);
//   }

//   server.on("/", homePage);
//   server.on("/time", handleTime);
//   server.on("/saveSchedule", handleSaveSchedule);
//   server.on("/saveReal", handleSaveRealTime);
//   server.begin();
//   Serial.println(WiFi.localIP());
//   myTime.hour = 23;
//   myTime.minute = 39;
//   myTime.second = 50;
//   myTime.hourAlarm.morning = 23;
//   myTime.minuteAlarm.morning = 40;
//   delay(1000);
// }

// void loop() {
//   if(activeAlarm) {
//     digitalWrite(LED_PIN, HIGH);
//     tone(BUZZER, 1000); 
//   } else {
//     digitalWrite(LED_PIN, LOW);
//     noTone(BUZZER); 
//   }

//   Serial.println("-------------------");
//   Serial.print("Time: ");
//   Serial.print(myTime.hour);  
//   Serial.print(":");
//   Serial.print(myTime.minute);
//   Serial.print(":");
//   Serial.println(myTime.second);
//   Serial.println("Active alarm: " + String(activeAlarm));
//   Serial.println("morning: " + String(myTime.hourAlarm.morning) + ":" + String(myTime.minuteAlarm.morning));
//   Serial.println("noon: " + String(myTime.hourAlarm.afternoon) + ":" + String(myTime.minuteAlarm.afternoon));
//   Serial.println("evening: " + String(myTime.hourAlarm.evening) + ":" + String(myTime.minuteAlarm.evening));
//   Serial.println("Drawer: " + String(drawer));
//   Serial.println("===================");
//   delay(1000);
//   server.handleClient(); 
// }


#include <LiquidCrystal_I2C.h>
#include "Time.h"
#include "web.h"

#define LED_PIN 8 
#define BUZZER 7
#define LED1 8
#define LED2 9
#define BUZZER 7
#define BUTTON 6
#define SDA 4
#define SCL 5
#define sensor1 10
bool button_state = false;
unsigned long pre_time = 0;
unsigned long time2 = 0;

bool activeAlarm = false;
uint8_t status = 0;
uint8_t drawer = 1;

LiquidCrystal_I2C lcd(0x27, 20, 4);
Time myTime;
WebServer server(80);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  ledcSetup(0, 1000, 8);
  ledcAttachPin(BUZZER, 0);
  timerInit();
  webInit();
  
}

void loop() {
  if(activeAlarm) {
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER, 1000); 
  } else {
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER); 
  }

  Serial.println("-------------------");
  Serial.print("Time: ");
  Serial.print(myTime.hour);  
  Serial.print(":");
  Serial.print(myTime.minute);
  Serial.print(":");
  Serial.println(myTime.second);
  Serial.println("Active alarm: " + String(activeAlarm));
  Serial.println("morning: " + String(myTime.hourAlarm.morning) + ":" + String(myTime.minuteAlarm.morning));
  Serial.println("noon: " + String(myTime.hourAlarm.afternoon) + ":" + String(myTime.minuteAlarm.afternoon));
  Serial.println("evening: " + String(myTime.hourAlarm.evening) + ":" + String(myTime.minuteAlarm.evening));
  Serial.println("Drawer: " + String(drawer));
  Serial.println("===================");
  delay(1000);
  server.handleClient(); 
}
