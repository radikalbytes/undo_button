#include <Adafruit_NeoPixel.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      2

#define  _interval  60000

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);

#include <TrinketKeyboard.h>

#define buttonPin 1

void put_color(int _r, int _g, int _b);

int __r = 0, __g = 250, __b = 0;
unsigned long time1 = 0,time2 = 0;

void setup()
{
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);

  // start USB stuff
  TrinketKeyboard.begin();
  pixels.begin(); // This initializes the NeoPixel library.

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

  if (digitalRead(buttonPin) == HIGH)
  {
    TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_Z);
    // this should type a CTRL+Z
    TrinketKeyboard.pressKey(0, 0);
    // this releases the key
    put_color(250,0,250); 
    if (__g > 0) {
        __r = __r + 25;
        __g = __g - 25;
    }
    for (int _pollDelay = 0; _pollDelay < 40; _pollDelay++){
        delay(5);
        TrinketKeyboard.poll(); 
    }
    put_color(__r, __g, __b); 
  }
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

void put_color(int _r, int _g, int _b){
  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(_g,_r,_b)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    //delay(delayval); // Delay for a period of time (in milliseconds).
  }
}
