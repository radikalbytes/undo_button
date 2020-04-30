/*
Copyright 2020 Alfredo Prado Vega
@radikalbytes
http://www.radikalbytes.com
This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License. To view a copy of this license, visit
http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to
Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

Neopixel library and Trinket keyboard library are from adafruit.com and have their 
own license. Please check it at adafruit.com
https://github.com/adafruit/Adafruit-Trinket-USB/tree/master/TrinketKeyboard
https://github.com/adafruit/Adafruit_NeoPixel

*/


// Adafruit Neopixel Library
#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            0

// How many NeoPixels are attached to the circuit?
#define NUMPIXELS      2
// Interval in ms to down button color
#define  _interval  60000

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

// Adafruit Trinket Keyboard library
#include <TrinketKeyboard.h>

// Pin button
#define buttonPin 1

// Functions definition
void put_color(int _r, int _g, int _b);

// Button RGB values
int __r = 0, __g = 250, __b = 0;
// Delay aux
unsigned long time1 = 0,time2 = 0;

// Setup routine
void setup()
{
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // start USB stuff
  TrinketKeyboard.begin();
  pixels.begin(); // This initializes the NeoPixel library.
  // Put initial color (green)
  put_color(__r, __g, __b);

  time1 = millis();
}

void loop()
{
  TrinketKeyboard.poll();
  // the poll function must be called at least once every 10 ms
  // or cause a keystroke
  // if it is not, then the computer may think that the device
  // has stopped working, and give errors

  if (digitalRead(buttonPin) == HIGH)  // button pushed
  {
    TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_Z);
    // this should type a COMMAND+Z for MAC
    // TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL, KEYCODE_Z);
    // this should type a CONTROLL+Z for Windows
    TrinketKeyboard.pressKey(0, 0);
    // this releases the key
    
    put_color(250,0,250); // put color purple 
    // change next step from green to red
    if (__g > 0) {
        __r = __r + 25;
        __g = __g - 25;
    }

    // Delay 200ms with pollig each 5 ms
    for (int _pollDelay = 0; _pollDelay < 40; _pollDelay++){
        delay(5);
        TrinketKeyboard.poll(); 
    }
    // Change button color
    put_color(__r, __g, __b); 
  }

  // If button not pushed in an interval of time, down one level
  // from red to green
  time2 = millis(); 
  if (time2 > (time1 + _interval)){
    time1 = millis();
    if (__r > 0) {
        __r = __r - 25;
        __g = __g + 25;
        put_color(__r, __g, __b);
    }
    
  }
}

// Send color to neopixels
void put_color(int _r, int _g, int _b){
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(_g,_r,_b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
