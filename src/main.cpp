/*
The MIT License (MIT)
*/
#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>

// #include <Adafruit_GFX.h>
// #include <Adafruit_ILI9341.h>

#include <FS.h>
#include <SPIFFS.h>

#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define BUTTON_0 38
#define TFT_LED 4

const char *ssid = "your ssid";
const char *password = "password";

// Colors
int TFT_COLOR;
#define BACKGROUND_COLOR 0x0000

// Bitmap_WiFi
extern uint8_t wifi_1[];
extern uint8_t wifi_2[];
extern uint8_t wifi_3[];

int WIFI_CONNECTED = false;

void setup()
{
  Serial.begin(115200);
  Serial.println("GO!");

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);

  Serial.println("Lights on!");

  pinMode(BUTTON_0, INPUT);

  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  Serial.println("TFT inited!");

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setTextColor(TFT_WHITE);
  tft.setTextWrap(true);
  tft.setCursor(0, 170);
  tft.setTextSize(2);

  tft.println(">>> Connecting to: ");
  tft.println(" ");
  tft.println(ssid);

  WiFi.begin(ssid, password);

  int ccnt = 0;

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    tft.drawBitmap(70, 50, wifi_1, 100, 100, TFT_WHITE);
    delay(200);
    tft.drawBitmap(70, 50, wifi_2, 100, 100, TFT_WHITE);
    delay(200);
    tft.drawBitmap(70, 50, wifi_3, 100, 100, TFT_WHITE);
    delay(200);
    tft.fillRect(70, 50, 100, 100, BACKGROUND_COLOR);
    ccnt += 1;

    if (ccnt > 7)
      break;
  }

  tft.fillScreen(BACKGROUND_COLOR); // Clear Screen

  tft.setTextColor(TFT_WHITE);
  tft.setCursor(20, 150);
  tft.setTextSize(2);
  tft.println("HELLO WORLD!");
  tft.drawLine(0, 130, 240, 130, TFT_WHITE);
  tft.drawLine(0, 185, 240, 185, TFT_WHITE);
}

int cnt = 0;

void loop()
{
  tft.setTextSize(1);
  tft.setTextColor(TFT_YELLOW);
  tft.setCursor(10, 10);

  WIFI_CONNECTED = WiFi.status() == WL_CONNECTED;

  if (WIFI_CONNECTED)
  {
    tft.print("Wifi: ");
    tft.println(ssid);
  }
  else
  {
    tft.println("Wifi: not connected");
  }

  tft.fillRect(0, 40, 240, 80, BACKGROUND_COLOR);
  tft.setTextSize(4);
  tft.setCursor(10, 50);
  tft.println(String(cnt));

  cnt += 1;

  if (cnt > 100)
    cnt = 0;

  if (digitalRead(BUTTON_0) == LOW)
  {
    tft.setTextSize(2);
    tft.setTextColor(TFT_RED);
    tft.setCursor(10, 250);
    tft.println("button1 pressed");
  }
  else
  {
    tft.setTextSize(2);
    tft.setTextColor(TFT_BLACK);
    tft.setCursor(10, 250);
    tft.println("button1 pressed");
  }
}
