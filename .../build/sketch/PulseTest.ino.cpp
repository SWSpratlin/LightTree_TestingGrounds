#include <Arduino.h>
#line 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 8
#define BRIGHTNESS 100
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

CRGB leds[NUM_LEDS];

#line 13 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void setup();
#line 22 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void loop();
#line 13 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void setup()
{
    delay(3000);
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}

void loop()
{
    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Red;
        delay(50);
        // leds[(i - 5)] = CRGB::Black;
        FastLED.show();
    }

    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Green;
        delay(50);
        FastLED.show();
    }
}
