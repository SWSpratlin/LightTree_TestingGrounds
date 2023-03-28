# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino" 2
# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
CRGB leds[150];

void setup()
{
    delay(3000);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
    FastLED.addLeds<WS2812B, 8, GRB>(leds, 150);
    FastLED.setBrightness(100);
    FastLED.show();
}

void loop()
{
    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Red;
        delay(50);
        FastLED.setBrightness(0);
        FastLED.show();
    }

    for (int i = 0; i < sizeof(leds); i++)
    {
        leds[i] = CRGB::Green;
        delay(50);
        FastLED.show();
    }
}
