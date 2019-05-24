/*
The MIT License (MIT)
*/

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS 27
#define TFT_DC 32
#define TFT_MOSI 23
#define TFT_CLK 18
#define TFT_RST 5
#define TFT_MISO 12
#define TFT_LED 4

#define BUTTON_0 38

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

const char *ssid = "your ssid";
const char *password = "password";

// Colors
int ILI9341_COLOR;
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

  pinMode(BUTTON_0, INPUT);

  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(BACKGROUND_COLOR);
  tft.setTextColor(ILI9341_WHITE);
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
    tft.drawBitmap(70, 50, wifi_1, 100, 100, ILI9341_WHITE);
    delay(200);
    tft.drawBitmap(70, 50, wifi_2, 100, 100, ILI9341_WHITE);
    delay(200);
    tft.drawBitmap(70, 50, wifi_3, 100, 100, ILI9341_WHITE);
    delay(200);
    tft.fillRect(70, 50, 100, 100, BACKGROUND_COLOR);
    ccnt += 1;

    if (ccnt > 7)
      break;
  }

  tft.fillScreen(BACKGROUND_COLOR); // Clear Screen

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(20, 150);
  tft.setTextSize(2);
  tft.println("HELLO WORLD!");
  tft.drawLine(0, 130, 240, 130, ILI9341_WHITE);
  tft.drawLine(0, 185, 240, 185, ILI9341_WHITE);
}

void loop()
{
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
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

  if (digitalRead(BUTTON_0) == LOW)
  {
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_RED);
    tft.setCursor(10, 250);
    tft.println("button1 pressed");
  }
  else
  {
    tft.fillRect(0, 250, 240, 260, ILI9341_BLACK);
  }
}
