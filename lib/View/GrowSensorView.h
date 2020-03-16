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
        float temperature;
        float humidity;
        MCUFRIEND_kbv tft;
        TSPoint p;
        bool temp_changed;
        bool humidity_changed;

    public:
        GrowSensorView();
        ~GrowSensorView();
        void Setup();
        void Display_Temp_Humidity();
        void Status(String msg);
        void SetTemperature(float t);
        void SetHumidity(float h);
};