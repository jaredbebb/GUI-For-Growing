#include <Arduino.h>
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
#include "GrowSensorView.h"

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	GREEN   0x07E0
#define WHITE   0xFFFF

// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65


GrowSensorView::GrowSensorView(){
  temperature = 0.0;
  humidity = 0.0;
}
GrowSensorView::~GrowSensorView(){

}

void GrowSensorView::Setup(void) {
  FindShieldIdentifier();
  tft.begin(shieldIdentifier);
  tft.setRotation(2);
  tft.fillScreen(BLACK);
  Status(F("Setup Screen"));
}

void GrowSensorView::Loop(){
  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(GREEN);    tft.setTextSize(2);
  tft.print("Humidity: ");
  tft.print(humidity);
  tft.println();
  tft.print("Temp: ");
  tft.print(temperature);
  tft.print(" *F");
  tft.println();
}

void GrowSensorView::Status(String msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

void GrowSensorView::SetTemperature(float t){temperature=t;}
void GrowSensorView::SetHumidity(float h){humidity=h;}

uint16_t GrowSensorView::FindShieldIdentifier(){
  Serial.begin(9600);
  Serial.println(F("TFT LCD test"));

  #ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.8\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Elegoo 2.8\" TFT Breakout Board Pinout"));
  #endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  shieldIdentifier = tft.readID();

  if(shieldIdentifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if(shieldIdentifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if(shieldIdentifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  }else if(shieldIdentifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if(shieldIdentifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if(shieldIdentifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if(shieldIdentifier==0x0101)
  {     
      shieldIdentifier=0x9341;
      Serial.println(F("Found 0x9341 LCD driver"));
  }else {
    Serial.print(F("Unknown LCD driver chip: "));
    Serial.println(shieldIdentifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined!"));
    Serial.println(F("Also if using the breakout, double-check that all wiring"));
    Serial.println(F("matches the tutorial."));
    shieldIdentifier=0x9341;
  }
  return shieldIdentifier;
}
