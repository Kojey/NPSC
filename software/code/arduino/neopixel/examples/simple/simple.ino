// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      1

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second
int px_value[11] = {0,26,51,77,102,128,153,179,204,230,255};
int px = px_value[10];
void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
 // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    //pixels.setPixelColor(0, pixels.Color(255,255,0)); // Moderately bright green color.
  pinMode(13,OUTPUT);
    pixels.show();
}

void loop() {
  static bool on = true;
  if(on){
    pixels.setPixelColor(0, pixels.Color(0,0,255));
    digitalWrite(13,HIGH);
    on = false;
  }else{
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    digitalWrite(13,LOW);
    on = true;
  }
  pixels.show();
  delay(1000);
  
}
