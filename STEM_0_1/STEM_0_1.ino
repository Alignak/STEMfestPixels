#include <Adafruit_NeoPixel.h>
#define neoPin       10
#define numPixels    60

#ifdef __AVR__
#include <avr/power.h>
#endif

int buttonPins[3] = {7, 8, 9};
int switchPin = 6;
int ledPins[4] = {2, 3, 4, 5};
int state = 0;
double neoTick = 0;
int counter = 0;
int pState = 0;
int tickLength = 500;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixels, neoPin, NEO_GRB + NEO_KHZ800);

int delayval = 100;
//STEM Fest Neopixel Design

void setup() {
  Serial.begin(9600);
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  pixels.begin();
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 6; i <= 9; i++) {
    pinMode(i, INPUT);
  }
}

void loop() {
  if (digitalRead(6) == HIGH) { // If switch is ON

    for (int i = 7; i <= 9; i++) { // For each button
      //      Serial.print("t");
      if (digitalRead(i) == HIGH) { // If button is pressed
        state = i - 7; // Switch states depending on the button pressed
      }
    }
    //    Serial.println();
    if (pState != state) {
      for (int i = 0; i < numPixels; i++) { // For each NeoPixel
        //        Serial.print("p");
        //        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn the NeoPixel off
      }
      //      Serial.println();
      pixels.show();
    }
    digitalWrite(2, HIGH);  // Set the running LED on
    for (int i = 3; i <= 5; i++) { // For each state led
      //      Serial.print("l");
      digitalWrite(i, LOW); // Turn off
    }
    //    Serial.println();
    digitalWrite(state + 3, HIGH); // Turn on the state LED depending on the current state
    if (neoTick + tickLength < millis()) { // If it's been 500 milliseconds since the last change in neoPixels
      neoTick = millis(); // Reset the timer
      Serial.println(millis());
      counter++; // Step up the counter
      if (counter >= 10) { // If the counter has exceeded the controlled area
        counter = 0; // Reset the counter to 0
      }
      //      Serial.println(counter);
    }

    switch (state) { // Depending on the state
      case 0://   Standby mode
        for (int i = 0; i < numPixels; i++) { // For each neoPixel
          //          Serial.print("s");
          if ((i + counter) % 10 < 5) { // For every 5 set
            pixels.setPixelColor(i, pixels.Color(200, 0, 0)); // Set the pixel color to red
          } else {
            pixels.setPixelColor(i, pixels.Color(200, 200, 200)); // Set the pixel color to white
            //first five pixels red
            //second five pixels while
          }
        }
        //        Serial.println();
        break;
      case 1: // Attention attraction

        break;
      case 2: // During a talk

        break;
    }

  } else { // If the switch is off
    for (int i = 2; i <= 5; i++) { // For each LED
      digitalWrite(i, LOW); // Turn the LED off
    }
    for (int i = 0; i < numPixels; i++) { // For each NeoPixel
      //      Serial.print("o");
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Turn the NeoPixel off
    }
  }
  pixels.show(); // Update the NeoPixels
  pState = state;
}

