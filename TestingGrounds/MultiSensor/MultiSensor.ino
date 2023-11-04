#include <FastLED.h>

// Defining Global Immutable Variables
#define NUM_LEDS 150
#define DATA_ONE 8
#define DATA_TWO 9
#define DATA_THREE 10
#define DATA_FOUR 11
#define DATA_FIVE 12
#define BRIGHTNESS 90
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

// Threshold for Distance Sensor
#define THRESHOLD 50

// Sensor Pin Designations
const int ECHO_PIN = 20;
const int TRIGGER_PIN = 21;

const int ECHO_PIN02 = 22;
const int TRIGGER_PIN02 = 23;

const int ECHO_PIN03 = 24;
const int TRIGGER_PIN03 = 25;

const int ECHO_PIN04 = 26;
const int TRIGGER_PIN04 = 27;

const int ECHO_PIN05 = 28;
const int TRIGGER_PIN05 = 29;

// Declaring arrays
CRGB leds[NUM_LEDS];
CRGB secondLeds[NUM_LEDS];
CRGB thirdLeds[NUM_LEDS];
CRGB fourthLeds[NUM_LEDS];
CRGB fifthLeds[NUM_LEDS];

// Distance variable for spacing
int delayDistance = 1;

// Head Variables
// These will be some of the main differences in this code
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

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;
int pulseColorWhite = 0;

void setup()
{
    // PinModes for US Sensor
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Setup the LED strips
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);

    // Set up pins for LED arrays.
    // Important to note that I'll be setting
    // up the pins rather than strips. I have 5 total
    // possibilities
    FastLED.addLeds<LED_TYPE, DATA_ONE, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_TWO, COLOR_ORDER>(secondLeds, NUM_LEDS);
    FastLED.addLeds<LED_TYPE, DATA_THREE, COLOR_ORDER>(thirdLeds, NUM_LEDS);

    // Set global brightness value
    FastLED.setBrightness(BRIGHTNESS);

    // Show the first Instances of the LEDs
    FastLED.show();

    // startup Delay to give things some breathing room
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
    pulse(leds, NUM_LEDS, pulseColorBlue, headBlue, 20);

    // call the first yellow pulse
    pulse(leds, NUM_LEDS, pulseColorYellow, headYellow, 40);

    // call the first green pulse
    pulse(leds, NUM_LEDS, pulseColorGreen, headGreen, 60);

    // call first white pulse
    pulse(leds, NUM_LEDS, pulseColorWhite, headWhite, 100);

    // call the second red pulse
    pulse(secondLeds, NUM_LEDS, pulseColorRed, secondHeadRed, 40);

    // call the second blue pulse
    pulse(secondLeds, NUM_LEDS, pulseColorBlue, secondHeadBlue, 60);

    // Call the second string Orange pulse
    pulse(secondLeds, NUM_LEDS, pulseColorYellow, secondHeadYellow, 0);

    // call second string green pulse
    pulse(secondLeds, NUM_LEDS, pulseColorGreen, secondHeadGreen, 20);

    // call second white pulse
    pulse(secondLeds, NUM_LEDS, pulseColorWhite, secondHeadWhite, 100);

    // Call third blue pulse
    pulse(thirdLeds, NUM_LEDS, pulseColorBlue, thirdHeadBlue, 0);

    // Call the third Red Pulse
    pulse(thirdLeds, NUM_LEDS, pulseColorRed, thirdHeadRed, 20);

    // Call the third Green Pulse
    pulse(thirdLeds, NUM_LEDS, pulseColorGreen, thirdHeadGreen, 40);

    // Call the third Yellow Pulse
    pulse(thirdLeds, NUM_LEDS, pulseColorYellow, thirdHeadYellow, 60);

    // Call the third White Pulse
    pulse(thirdLeds, NUM_LEDS, pulseColorWhite, thirdHeadWhite, 100);

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
void pulse(CRGB strip[], const int &ledNumber, int distSensor, int &color, int &head, int gap)
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
    //  address Trigger Pin directly. Sets to low
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    //  address Trigger Pin directly. Sets to high
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    // address Trigger Pin directly. Sets to low
    digitalWrite(TRIGGER_PIN, LOW);

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