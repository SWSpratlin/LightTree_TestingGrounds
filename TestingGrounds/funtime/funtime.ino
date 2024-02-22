#include <FastLED.h>

#define NUM_LEDS 150
#define DATA_PIN 14
#define BRIGHTNESS 100
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000

// declare array
CRGB leds[NUM_LEDS];

// Trigger Pin for US Sensor
// const int TRIGGER_PIN = 2;

// Read/echo pin for US Sensor
// const int ECHO_PIN = 3;

// diatance variable
// int delayDistance = 1;

int headBlue = 0;
int headRed = -30;

void setup()
{
    // WE DO NEED THESE
    // pinMode(TRIGGER_PIN, OUTPUT);
    // pinMode(ECHO_PIN, INPUT);

    // Begin serial communication BAUD 9600
    Serial.begin(115200);

    // Setup LED strip power
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);

    // add specific LEDs to array
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

    // set LED brightness
    FastLED.setBrightness(BRIGHTNESS);

    // show LEDs
    FastLED.show();

    // starup delay 1 second
    delay(1000);
}

void loop()
{
    // update pulse distance
    // measureDist(delayDistance);

    // call red pulse
    pulse(CRGB::Red, headRed, 0);

    // call blue pulse
    pulse(CRGB::Blue, headBlue, 35);

    // JAY IS GOING TO DO SOMETHING FUN HERE
    FastLED.show();

    // print delayDistance to serial monitor
    Serial.print(headBlue);
    Serial.print("  ");
    Serial.println(headRed);
    delay(1);
}

void pulse(CRGB color, int &head, int gap)
{

    // Increment until it hits the end
    if (head <= NUM_LEDS)
    {
        head++;
    }

    // reset if too high
    if (head > NUM_LEDS)
    {
        head = 0 - gap;
    }

    // writing color to the head
    if (head >= 0)
    {
        // color the LEDs
        leds[head] = color;
    }

    // Show updated LEDs
    FastLED.show();

    // Fade for size
    tailFade(250);
}

// Fade to determine the size of the pulse
void tailFade(int pulseSize)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        // 255 is standard, 215 is very small
        leds[i].nscale8(pulseSize);
    }
}

void backFill(int skipDistance, int head, CRGB color)
{

    for (int i = skipDistance; i > 0; i--)
    {
        int behind = head - i;

        if (behind >= 0)
        {
            leds[behind] = color;
        }
    }
}
