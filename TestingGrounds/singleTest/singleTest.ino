#include <FastLED.h>
#include <Arduino.h>

#define Data 17
// FastLED Vars
#define NUM_LEDS 150
#define BRIGHTNESS 90
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

CRGB leds[NUM_LEDS];

int headBlue = 0;
int headRed = -30;
int headGreen = -50;
int headYellow = -100;
int headWhite = -70;

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;
int pulseColorWhite = 0;

void setup()
{
    // Setup the LED strips
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
    FastLED.addLeds<LED_TYPE, Data, COLOR_ORDER>(leds, NUM_LEDS);
    // Set global brightness value
    FastLED.setBrightness(BRIGHTNESS);

    // Show the first Instances of the LEDs
    FastLED.show();

    // startup Delay to give things some breathing room
    delay(1000);
    Serial.begin(9600);
}

void loop()
{
    pulse(leds, NUM_LEDS, pulseColorRed, headRed, 0);
    pulse(leds, NUM_LEDS, pulseColorBlue, headBlue, 20);
    pulse(leds, NUM_LEDS, pulseColorYellow, headYellow, 40);
    pulse(leds, NUM_LEDS, pulseColorGreen, headGreen, 60);
    pulse(leds, NUM_LEDS, pulseColorWhite, headWhite, 100);
    FastLED.show();
}
void pulse(CRGB strip[], const int &ledNumber, int &color, int &head, int gap)
{

    // Increment until it hits the end
    if (head <= ledNumber)
    {
        head++;
    }

    // reset if too high
    if (head > ledNumber)
    {
        head = 0 - gap;
    }

    // Fade for size
    tailFade(strip, ledNumber, 250);
    delay(1);
}

// Fade to determine the size of the pulse
void tailFade(CRGB strip[], int ledNumber, int pulseSize)
{
    for (int i = 0; i < ledNumber; i++)
    {
        // 255 is standard, 215 is very small
        strip[i].nscale8(pulseSize);
    }
}