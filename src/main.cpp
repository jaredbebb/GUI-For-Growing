#include <Arduino.h>
#include <SPI.h>
#include "DHT.h"
#include "GrowSensorView.h"
//#define DHTPIN 2    
#define DHTPIN 22  
#define DHTTYPE DHT22   

const int led_pin=PB5;

// Counter and compare values
const uint16_t t1_load = 0;
const uint16_t t1_comp = 31250;
uint16_t demo = 0;


DHT dht(DHTPIN, DHTTYPE);
GrowSensorView growsensorview;


void timer_setup(){
  // set led pin to be output
  DDRB |= (1 << led_pin); 
  
  // Reset Timer1 Control Reg A
  TCCR1A = 0;

  // Set to prescaler of 256
  TCCR1B |= (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  // Reset timer1 and set compare value
  TCNT1 = t1_load;
  OCR1A = t1_comp;

  // Enable Timer1 compare interrupt
  TIMSK1 = (1 << OCIE1A);

  // Enable global interrupts
  sei(); 
}


void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
  timer_setup();

  //GrowSensorView setup
  growsensorview.Setup();
}


void read_temp_and_humidity(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  growsensorview.SetHumidity(h);
  growsensorview.SetTemperature(f);
  growsensorview.Display_Temp_Humidity();
}

void loop() {
}

ISR(TIMER1_COMPA_vect){
  TCNT1 = t1_load;
  PORTB ^= (1 << led_pin);
  read_temp_and_humidity();
}
