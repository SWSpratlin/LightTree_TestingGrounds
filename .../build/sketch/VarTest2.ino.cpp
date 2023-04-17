#include <Arduino.h>
#line 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
#include <FastLED.h>
// this is imporant for the code to run

#define NUM_LEDS 150
#define NUM_SECOND 300
#define DATA_PIN 8
#define DATA_TWO 10
#define BRIGHTNESS 100
#define COLOR_ORDER GRB
// #define COLOR_ORDER_SECOND RGB
#define LED_TYPE WS2812B
// #define LED_TYPE_SECOND WS2811
#define VOLTS 5
#define MAX_MA 3000

// Threshold for the distance in which the color change triggers
#define THRESHOLD 50

// declare array
CRGB leds[NUM_LEDS];
CRGB secondLeds[NUM_SECOND];

// Read/echo pin for US Sensor
const int ECHO_PIN = 2;

// diatance variable
int delayDistance = 1;

// Head variables
int headBlue = -10;
int headRed = -30;
int headGreen = -50;
int headYellow = -100;

int secondHeadBlue = 0;
int secondHeadRed = -35;
int secondHeadGreen = -50;
int secondHeadOrange = -100;

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;

#line 46 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void setup();
#line 70 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void loop();
#line 110 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void pulse(CRGB strip[], const int &ledNumber, int &color, int &head, int gap);
#line 148 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void tailFade(CRGB strip[], int ledNumber, int pulseSize);
#line 162 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
int headSkip(int &distance);
#line 183 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void backFill(CRGB strip[], int skipDistance, int head, int color);
#line 201 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void measureDist(int &distance);
#line 228 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
int colorChange(int &color);
#line 46 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
void setup()
{
    // WE DO NEED THESE
    pinMode(3, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Setup LED strip power
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);

    // add specific LEDs to array
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_TWO, COLOR_ORDER>(secondLeds, NUM_SECOND);

    // set LED brightness
    FastLED.setBrightness(BRIGHTNESS);

    // show LEDs
    FastLED.show();

    // starup delay .5 second
    delay(500);
    Serial.begin(9600);
}

void loop()
{
    // update pulse distance
    measureDist(delayDistance);

    // call first red pulse
    pulse(leds, NUM_LEDS, pulseColorRed, headRed, 0);

    // call the first blue pulse
    pulse(leds, NUM_LEDS, pulseColorBlue, headBlue, 10);

    // call the first yellow pulse
    pulse(leds, NUM_LEDS, pulseColorYellow, headYellow, 20);

    // call the first green pulse
    pulse(leds, NUM_LEDS, pulseColorGreen, headGreen, 30);

    // call the second red pulse
    pulse(secondLeds, NUM_SECOND, pulseColorRed, secondHeadRed, 20);

    // call the second blue pulse
    pulse(secondLeds, NUM_SECOND, pulseColorBlue, secondHeadBlue, 30);

    // Call the second string Orange pulse
    pulse(secondLeds, NUM_SECOND, pulseColorYellow, secondHeadOrange, 0);

    // call second string green pulse
    pulse(secondLeds, NUM_SECOND, pulseColorGreen, secondHeadGreen, 10);

    // Update the changes. Putting this in the Pulse function makes things go much slower
    // Updating the pixels THEN showing the changes is much faster.
    FastLED.show();
    Serial.println(delayDistance);
}

/**
 * Pulse function. intakes Strip Number(the declaration of the LED Strip as an array)
 * NUmber of LEDs in the strip, the color of the pulse, the head variable you want,
 * and the gap between pulses
 */
void pulse(CRGB strip[], const int &ledNumber, int &color, int &head, int gap)
{

    // Get the head skip
    int skip = headSkip(delayDistance);

    // Increment until it hits the end
    if (head <= ledNumber)
    {
        head += skip;
    }

    // reset if too high
    if (head > ledNumber)
    {
        head = 0 - gap;
    }

    // writing color to the head
    if (head >= 0)
    {
        // color the LEDs
        strip[head] = CHSV(colorChange(color), 255, 255);

        // backfill for skipped LEDs
        backFill(strip, skip, head, color);
    }

    // Fade for size
    tailFade(strip, ledNumber, 250);
    delay(1);
}

/**
 * Fade the tail of the LEDs to determine the visual size of the pulse
 * Needs an input between 254 and 200 (200 being the smallest)
 */
// Fade to determine the size of the pulse
void tailFade(CRGB strip[], int ledNumber, int pulseSize)
{
    for (int i = 0; i < ledNumber; i++)
    {
        // 255 is standard, 215 is very small
        strip[i].nscale8(pulseSize);
    }
}

/**
 * Determines the skip distance when interacting with the sensor
 * so that the closer a subject is, the more LEDs the pulse will skip
 *
 */
int headSkip(int &distance)
{
    // translate Sensor reading into headskip scale
    if (40 <= distance)
    {
        return 1;
    }
    else if (20 <= distance < 40)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

/**
 * Fill in behind the Head when it skips (speeds up) an LED
 * Takes in the distance which is updated every loop
 */
void backFill(CRGB strip[], int skipDistance, int head, int color)
{

    for (int i = skipDistance; i > 0; i--)
    {
        int behind = head - i;

        if (behind >= 0)
        {
            strip[behind] = CHSV(colorChange(color), 255, 255);
        }
    }
}

/**
 * Distance measurement. C statement address the pin directly which eliminate the need
 * for digitalWrite();
 */
void measureDist(int &distance)
{
    // C statement to address Trigger Pin directly. Sets to low
    PORTE |= _BV(PE5);
    delayMicroseconds(2);
    // C Statement to address Trigger Pin directly. Sets to high
    PORTE &= ~_BV(PE5);
    delayMicroseconds(10);
    // C Statement to address Trigger Pin directly. Sets to low
    PORTE |= _BV(PE5);

    // Equation for distance calculation condensed into "return"
    // divided by 4 to eliminate "pulseDistance"
    long readerValue = pulseIn(ECHO_PIN, HIGH);
    // Serial.println(readerValue);
    if (readerValue < 9)
    {
        readerValue = 9;
    }

    distance = readerValue * 0.034 / 2;
}

/**
 * Change the color in tandem with the distance measurement. Will only
 * activate within a certain threshold
 */
int colorChange(int &color)
{
    // Check if there's something within the area of the sensor
    if (delayDistance < THRESHOLD)
    {
        // Resetr the color variable to 0 when it hits 256 (loop)
        if (color > 255)
        {
            color = 0;
        }
        // increment the color if there's something on the sensor.
        color++;
    }
    // return the updated value
    return color;
}
