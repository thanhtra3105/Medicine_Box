#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Time.h"
#include "web.h"

#define LED1 8
#define LED2 9
#define BUZZER 7
#define BUTTON 6
#define SDA 4
#define SCL 5
#define IR1 2
#define IR2 3
#define LDR_PIN 0
#define LDR_LED 10

const int channel = 1;
const int freq = 5000;
const int resolution = 8;

volatile bool button_state = false;
unsigned long pre_time = 0;
unsigned long time2 = 0;
volatile bool activeAlarm = false;
volatile bool activeFlag  = false;

bool alarmFlag = false;
uint8_t status = 0; 
uint8_t drawer[3] = {1,1,1}; // ngan 1, ngan 2, ngan 3
uint8_t currentDrawer = 1;
LiquidCrystal_I2C lcd(0x27, 20, 4);
Time myTime;
WebServer server(80);

void IRAM_ATTR handleButton()
{
  if(activeAlarm && alarmFlag)
    button_state = true;
}

void handleLDR()
{
  float LDR_VALUE = analogRead(LDR_PIN);
  // Serial.println(LDR_VALUE);
  // int LDR_LED_VALUE = map(LDR_VALUE, 0, 4095, 0, 255);
  if(LDR_VALUE > 3700)
    digitalWrite(LDR_LED, 1);
  else 
    digitalWrite(LDR_LED, 0);
}

void setup()
{
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(LDR_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // ledcSetup(channel, freq, resolution);
  // ledcAttachPin(LDR_LED, channel);

  ledcSetup(0, 1000, 8);
  ledcAttachPin(BUZZER, 0);
  //ledcAttachPin(LDR_LED, channel);

  Wire.begin(SDA, SCL);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(BUTTON, INPUT_PULLUP);
  digitalWrite(BUZZER, LOW);

  attachInterrupt(digitalPinToInterrupt(BUTTON), handleButton, FALLING);
  timerInit();
  webInit();
}

void loop()
{

  // bool irState1 = digitalRead(IR1);
  // bool irState2 = digitalRead(IR2);
  handleLDR();
  // Serial.println(irState1);
  // delay(100);
  Serial.println(button_state);

  Serial.println("Alarm: " + String(activeAlarm));
  if (activeAlarm) // den gio uong thuoc{
  {
    //Serial.println("Alarm active");
    if (alarmFlag)
    {
      tone(BUZZER, 1000);
      status = 1; // den gio uong thuoc]
      lcd.setCursor(6, 0);
      lcd.print("TU THUOC");
      lcd.setCursor(7, 1);
      lcd.print(myTime.hour < 10 ? "0" : "" + String(myTime.hour) + ":" +(myTime.minute < 10 ? "0" : "") + String(myTime.minute));
      lcd.setCursor(1, 2);
      lcd.print("DEN GIO UONG THUOC");
      lcd.setCursor(3,3);
      lcd.print("NGAN THUOC: " + String(currentDrawer));
      if (currentDrawer == 1) // ngan 1
      {
        // Serial.println("Ngan 1");
        digitalWrite(LED1, 1);
        digitalWrite(LED2, 0);
        while (digitalRead(IR1) == 1 && digitalRead(IR2) == 0) // lay sai qua ngan 2
        {
          lcd.setCursor(6, 0);
          lcd.print("TU THUOC");
          lcd.setCursor(3,2);
          lcd.print("SAI NGAN THUOC!!!");
          digitalWrite(LED2, 1);
          tone(BUZZER, 900);
          delay(50);
          digitalWrite(LED2, 0);
          noTone(BUZZER);
          delay(50);
          lcd.clear();
          
          //lcd.clear();
        }
      }
      else if (currentDrawer == 2)
      {
        // Serial.println("ngan 2");
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 1);

        while (digitalRead(IR1) == 0 && digitalRead(IR2) == 1) // lay sai qua ngan 1
        {
          
          lcd.setCursor(0,2);
          lcd.print(" SAI NGAN THUOC!!! ");
          digitalWrite(LED1, 1);
          tone(BUZZER, 900);
          delay(50);
          digitalWrite(LED1, 0);
          noTone(BUZZER);
          delay(50);
          lcd.clear();
        }
      }

      if (button_state) // da nhan thuoc
      {
        button_state = false;
        alarmFlag = false;
        activeFlag = false;
        noTone(BUZZER);
        digitalWrite(LED1, 0);
        digitalWrite(LED2, 0);

      }
    }
    else if(alarmFlag == false && activeFlag == false)
    {
      // Serial.println("Da nhan thuoc");
      //lcd.clear();
      lcd.setCursor(0, 2);
      lcd.print("   DA NHAN THUOC   ");
      lcd.setCursor(3,3);
      lcd.print("              ");
      // status = 2; // Da lay thuoc
    }
  }
  else
  {
    // Serial.println("Chua den gio uong thuoc");
    activeFlag = true;
    alarmFlag = true;
    digitalWrite(LED1, 0);
    digitalWrite(LED2, 0);
    noTone(BUZZER);
    //lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("TU THUOC");
    lcd.setCursor(7, 1);
    lcd.print(myTime.hour < 10 ? "0" : "" + String(myTime.hour) + ":" +(myTime.minute < 10 ? "0" : "") + String(myTime.minute));
    lcd.setCursor(0, 2);
    lcd.print("    CHUA DEN GIO   ");
    lcd.setCursor(3,3);
    lcd.print("              ");


    status = 0; // chua toi gio
  }

  server.handleClient();
}
