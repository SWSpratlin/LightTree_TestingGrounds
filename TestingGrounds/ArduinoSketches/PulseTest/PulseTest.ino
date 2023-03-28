#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 10
#define BRIGHTNESS 10
#define COLOR_ORDER RBG
#define LED_TYPE WS2812B

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(10);
    FastLED.clear();
    FastLED.show();
}

void loop()
{
    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Red;
        FastLED.show();
    }
}