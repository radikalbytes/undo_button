#include <FastLED.h>
#define DATA_PIN    0
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
#define NUM_LEDS   2

#define BRIGHTNESS  255
#include "DigiKeyboard.h"  // Include Library for Keyboard Emulation / Before verifying the code , change the board to Digispark default .

#define  _interval  60000
#define _refresh 5000 
#define Purple 0x800080

void put_color(int32_t __color);

int buttonPin = 1;   
// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int32_t _color = 0x008000;
CRGB leds[NUM_LEDS];

unsigned long time1 = 0,time2 = 0;

void setup() {

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS); 

  put_color(_color);
  time1 = millis();

}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    DigiKeyboard.sendKeyStroke(0);
    if (_color < 0x800000) {
        _color = _color + 0x080000;
        _color = _color - 0x000800;
    }

    DigiKeyboard.sendKeyStroke(KEY_Z , MOD_GUI_LEFT);
    
    put_color(Purple); 
    DigiKeyboard.delay(200);
    put_color(_color); 

  }
  
  time2 = millis(); 
  if (time2 > (time1 + _interval)){
    time1 = millis();
    DigiKeyboard.sendKeyStroke(0);
    if (_color > 0x008000) {
        _color = _color - 0x080000;
        _color = _color + 0x000800;
        put_color(_color);
    }
    
  }
  
}

void put_color(int32_t __color){
    leds[0] = __color;
    leds[1] = __color;
    FastLED.show(); 
}
