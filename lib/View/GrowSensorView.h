#include <Arduino.h>
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>    
#include <TouchScreen.h>
#include <MCUFRIEND_kbv.h>
using namespace std; 

const int TEXT_LEN = 12;

class GrowSensorView{
    private:
        uint16_t shieldIdentifier;
        uint16_t FindShieldIdentifier();

    public:
        GrowSensorView();
        ~GrowSensorView();
        void Setup();
        void Loop();
        void Status(String msg);
        //MCUFRIEND_kbv tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
        MCUFRIEND_kbv tft;
        // TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
        TSPoint p;
        //TouchScreen ts;
        float temperature;
        float humidity;
        void SetTemperature(float t);
        void SetHumidity(float h);


};