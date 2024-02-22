#line 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
#include <Arduino.h>
#include <FastLED.h>

// Defining Global Immutable Variables

// Data pins for the LED Strips
#define DATA_ONE 16
#define DATA_TWO 17
#define DATA_THREE 18
#define DATA_FOUR 19
#define DATA_FIVE 21
#define DATA_SIX 22

// Pins for US Echoes
#define ECHO1 34
#define ECHO2 35
#define ECHO3 33

// Pins for the US Triggers
#define TRIGGER1 26
#define TRIGGER2 14
#define TRIGGER3 32

// FastLED Vars
#define NUM_LEDS 150
#define BRIGHTNESS 90
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

// Threshold for Distance Sensor
#define THRESHOLD 150

// Declaring arrays
CRGB leds[NUM_LEDS];
CRGB secondLeds[NUM_LEDS];
CRGB thirdLeds[NUM_LEDS];
CRGB fourthLeds[NUM_LEDS];
CRGB fifthLeds[NUM_LEDS];
CRGB sixthLeds[NUM_LEDS];

// Distance variable for spacing
int delayDistance1 = 1;
int delayDistance2 = 1;
int delayDistance3 = 1;

/*
Head Variables. Each pulse needs a head variable to iterate through the code with. The lower they go, the slower they will come out.
This is where a lot of the memory is going, as well as the pulse functions.
*/
int headBlue = 0;
int headRed = -30;
int headGreen = -50;
int headYellow = -100;
int headWhite = -70;

int secondHeadBlue = -10;
int secondHeadRed = -40;
int secondHeadGreen = -60;
int secondHeadYellow = -80;
int secondHeadWhite = -110;

int thirdHeadBlue = -5;
int thirdHeadRed = -25;
int thirdHeadGreen = -35;
int thirdHeadYellow = -55;
int thirdHeadWhite = -75;

int fourthHeadBlue = -5;
int fourthHeadRed = -45;
int fourthHeadGreen = -85;
int fourthHeadYellow = -55;
int fourthHeadWhite = -75;

int fifthheadBlue = 0;
int fifthheadRed = -40;
int fifthheadGreen = -60;
int fifthheadYellow = -120;
int fifthheadWhite = -90;

int sixthheadBlue = 0;
int sixthheadRed = -40;
int sixthheadGreen = -60;
int sixthheadYellow = -100;
int sixthheadWhite = -110;

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;
int pulseColorWhite = 0;

#line 95 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void setup();
#line 130 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void loop();
#line 188 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void pulse(CRGB strip[], const int &ledNumber, int &delayNumber, int &color, int &head, int gap);
#line 226 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void tailFade(CRGB strip[], int ledNumber, int pulseSize);
#line 240 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
int headSkip(int &distance);
#line 261 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void backFill(CRGB strip[], int &delayNumber, int skipDistance, int head, int color);
#line 279 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void measureDist(int trigger, int echo, int &distance);
#line 306 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
int colorChange(int &delayNumber, int &color);
#line 95 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/espLightTree/espLightTree.ino"
void setup()
{
    // PinModes for US Sensors
    pinMode(TRIGGER1, OUTPUT);
    pinMode(TRIGGER2, OUTPUT);
    pinMode(TRIGGER3, OUTPUT);
    pinMode(ECHO1, INPUT);
    pinMode(ECHO2, INPUT);
    pinMode(ECHO3, INPUT);

    // Setup the LED strips
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);

    // Set up pins for LED arrays.
    // Important to note that I'll be setting
    // up the pins rather than strips. I have 5 total
    // possibilities
    FastLED.addLeds<LED_TYPE, DATA_ONE, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_TWO, COLOR_ORDER>(secondLeds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_THREE, COLOR_ORDER>(thirdLeds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_ONE, COLOR_ORDER>(fourthLeds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_ONE, COLOR_ORDER>(fifthLeds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_ONE, COLOR_ORDER>(sixthLeds, NUM_LEDS);

    // Set global brightness value
    FastLED.setBrightness(BRIGHTNESS);

    // Show the first Instances of the LEDs
    FastLED.show();

    // startup Delay to give things some breathing room
    delay(1000);
    Serial.begin(115200);
}

void loop()
{
    // update pulse distance
    measureDist(TRIGGER1, ECHO1, delayDistance1);
    delay(10);
    measureDist(TRIGGER2, ECHO2, delayDistance2);
    delay(10);
    measureDist(TRIGGER3, ECHO3, delayDistance3);
    delay(10);

    // call first Strand Pulses
    pulse(leds, NUM_LEDS, delayDistance1, pulseColorRed, headRed, 0);
    pulse(leds, NUM_LEDS, delayDistance1, pulseColorBlue, headBlue, 20);
    pulse(leds, NUM_LEDS, delayDistance1, pulseColorYellow, headYellow, 40);
    pulse(leds, NUM_LEDS, delayDistance1, pulseColorGreen, headGreen, 60);
    pulse(leds, NUM_LEDS, delayDistance1, pulseColorWhite, headWhite, 100);

    // call second strand pulses
    pulse(secondLeds, NUM_LEDS, delayDistance1, pulseColorRed, secondHeadRed, 40);
    pulse(secondLeds, NUM_LEDS, delayDistance1, pulseColorBlue, secondHeadBlue, 60);
    pulse(secondLeds, NUM_LEDS, delayDistance1, pulseColorYellow, secondHeadYellow, 0);
    pulse(secondLeds, NUM_LEDS, delayDistance1, pulseColorGreen, secondHeadGreen, 20);
    pulse(secondLeds, NUM_LEDS, delayDistance1, pulseColorWhite, secondHeadWhite, 100);

    // Call third strand pulses
    pulse(thirdLeds, NUM_LEDS, delayDistance2, pulseColorBlue, thirdHeadBlue, 0);
    pulse(thirdLeds, NUM_LEDS, delayDistance2, pulseColorRed, thirdHeadRed, 20);
    pulse(thirdLeds, NUM_LEDS, delayDistance2, pulseColorGreen, thirdHeadGreen, 40);
    pulse(thirdLeds, NUM_LEDS, delayDistance2, pulseColorYellow, thirdHeadYellow, 60);
    pulse(thirdLeds, NUM_LEDS, delayDistance2, pulseColorWhite, thirdHeadWhite, 100);

    // call fourth Strand Pulses
    pulse(leds, NUM_LEDS, delayDistance2, pulseColorRed, fourthHeadRed, 0);
    pulse(leds, NUM_LEDS, delayDistance2, pulseColorBlue, fourthHeadBlue, 20);
    pulse(leds, NUM_LEDS, delayDistance2, pulseColorYellow, fourthHeadYellow, 40);
    pulse(leds, NUM_LEDS, delayDistance2, pulseColorGreen, fourthHeadGreen, 60);
    pulse(leds, NUM_LEDS, delayDistance2, pulseColorWhite, fourthHeadWhite, 100);

    // call fifth Strand Pulses
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorRed, fifthheadRed, 0);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorBlue, fifthheadBlue, 20);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorYellow, fifthheadYellow, 40);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorGreen, fifthheadGreen, 60);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorWhite, fifthheadWhite, 100);

    // call sixth Strand Pulses
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorRed, sixthheadRed, 0);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorBlue, sixthheadBlue, 20);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorYellow, sixthheadYellow, 40);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorGreen, sixthheadGreen, 60);
    pulse(leds, NUM_LEDS, delayDistance3, pulseColorWhite, sixthheadWhite, 100);

    // Update the changes. Putting this in the Pulse function makes things go much slower
    // Updating the pixels THEN showing the changes is much faster.
    FastLED.show();
    delay(1);
}

void pulse(CRGB strip[], const int &ledNumber, int &delayNumber, int &color, int &head, int gap)
{

    // Get the head skip
    int skip = headSkip(delayNumber);

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
        strip[head] = CHSV(colorChange(delayNumber, color), 255, 255);

        // backfill for skipped LEDs
        backFill(strip, delayNumber, skip, head, color);
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
    if (150 <= distance)
    {
        return 1;
    }
    else if (80 <= distance < 150)
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
void backFill(CRGB strip[], int &delayNumber, int skipDistance, int head, int color)
{

    for (int i = skipDistance; i > 0; i--)
    {
        int behind = head - i;

        if (behind >= 0)
        {
            strip[behind] = CHSV(colorChange(delayNumber, color), 255, 255);
        }
    }
}

/**
 * Distance measurement. C statement address the pin directly which eliminate the need
 * for digitalWrite();
 */
void measureDist(int trigger, int echo, int &distance)
{
    // C statement to address Trigger Pin directly. Sets to low
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    // C Statement to address Trigger Pin directly. Sets to high
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    // C Statement to address Trigger Pin directly. Sets to low
    digitalWrite(trigger, LOW);

    // Equation for distance calculation condensed into "return"
    // divided by 4 to eliminate "pulseDistance"
    long readerValue = pulseIn(echo, HIGH);
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
int colorChange(int &delayNumber, int &color)
{
    // Check if there's something within the area of the sensor
    if (delayNumber < THRESHOLD)
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
