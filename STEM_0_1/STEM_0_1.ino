#include <Adafruit_NeoPixel.h>
#define PIN         11
#define NUMPIXELS   300

#ifdef __AVR__
#include <avr/power.h>
#endif

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1iii00;
//STEM Fest Neopixel Design

void setup() {
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
}

void loop() {
  initialisePixels();
  for (int i = 1; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(delayval);
  }
}

void initialisePixels() {
  for (int i = 1; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(200,0,0));
  }
  pixels.show();
}

