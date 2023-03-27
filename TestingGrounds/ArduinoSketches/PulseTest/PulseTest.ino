#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 10

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2812B, DATA_PIN>(leds, NUM_LEDS);
}

void loop()
{
    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Red;
    }
}