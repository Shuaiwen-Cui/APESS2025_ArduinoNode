#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 4
#define LED_PIN 7

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  // Set all LEDs to green
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;
  }
  FastLED.show();
}

void loop() {
  // Do nothing
}
