# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/VarTest2/VarTest2.ino" 2
// this is imporant for the code to run


// #define NUM_SECOND 150

// #define DATA_TWO 10


// #define COLOR_ORDER_SECOND RGB

// #define LED_TYPE_SECOND WS2811



// Threshold for the distance in which the color change triggers


// declare array
CRGB leds[150];
// CRGB secondLeds[NUM_SECOND];

// Trigger Pin for US Sensor
const int TRIGGER_PIN = 2;

// Read/echo pin for US Sensor
const int ECHO_PIN = 3;

// diatance variable
int delayDistance = 1;

// Head variables
int headBlue = -10;
int headRed = -30;
int headGreen = -50;
int headYellow = -100;

// int secondHeadBlue = 0;
// int secondHeadRed = -35;
// int secondHeadGreen = -50;
// int secondHeadOrange = -100;

// Color variables (need to be global for them to change consistently)
int pulseColorRed = 250;
int pulseColorBlue = 150;
int pulseColorYellow = 30;
int pulseColorGreen = 100;

void setup()
{
    // WE DO NEED THESE
    pinMode(TRIGGER_PIN, 0x1);
    pinMode(ECHO_PIN, 0x0);

    // Begin serial communication BAUD 9600
    Serial.begin(9600);

    // Setup LED strip power
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);

    // add specific LEDs to array
    FastLED.addLeds<WS2812B, 8, GRB>(leds, 150);
    // FastLED.addLeds<LED_TYPE_SECOND, DATA_TWO, COLOR_ORDER_SECOND>(secondLeds, NUM_SECOND);

    // set LED brightness
    FastLED.setBrightness(100);

    // show LEDs
    FastLED.show();

    // starup delay 1 second
    delay(1000);
}

void loop()
{
    // update pulse distance
    measureDist(delayDistance);

    // call first red pulse
    pulse(leds, 150, pulseColorRed, headRed, 0);

    // call the first blue pulse
    pulse(leds, 150, pulseColorBlue, headBlue, 10);

    // call the first yellow pulse
    pulse(leds, 150, pulseColorYellow, headYellow, 20);

    // call the first green pulse
    pulse(leds, 150, pulseColorGreen, headGreen, 30);

    Serial.println(pulseColorRed);

    // call the second red pulse
    // pulse(secondLeds, NUM_SECOND, CRGB::Red, secondHeadRed, 20);

    // call the second blue pulse
    // pulse(secondLeds, NUM_SECOND, CRGB::Blue, secondHeadBlue, 30);

    // Call the second string Orange pulse
    // pulse(secondLeds, NUM_SECOND, CRGB::Orange, secondHeadOrange, 0);

    // call second string green pulse
    // pulse(secondLeds, NUM_SECOND, CRGB::Green, secondHeadGreen, 10);
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

    // Show updated LEDs
    FastLED.show();

    // Fade for size
    tailFade(strip, ledNumber, 250);
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
    if (50 <= distance)
    {
        return 1;
    }
    else if (30 <= distance < 50)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}

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

// Distance measurement
void measureDist(int &distance)
{
    digitalWrite(TRIGGER_PIN, 0x0);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, 0x1);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, 0x0);

    // Equation for distance calculation condensed into "return"
    // divided by 4 to eliminate "pulseDistance"
    long readerValue = pulseIn(ECHO_PIN, 0x1);
    // Serial.println(readerValue);
    if (readerValue < 9)
    {
        readerValue = 9;
    }

    distance = readerValue * 0.034 / 2;
}

int colorChange(int &color)
{
    if (delayDistance < 140)
    {
        if (color > 255)
        {
            color = 0;
        }
        color++;
    }
    return color;
}
