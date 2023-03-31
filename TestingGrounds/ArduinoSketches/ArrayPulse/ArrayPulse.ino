#include <FastLED.h>
#include <time.h>

#define NUM_LEDS 150
#define DATA_PIN 8
#define BRIGHTNESS 100
#define COLOR_ORDER GRB
#define LED_TYPE WS2812B
#define VOLTS 5
#define MAX_MA 3000
int pulseDistance;

CRGB leds[NUM_LEDS];

int f = 0;
int y = 0;
int a = 0;
int b = 0;
int c = 0;
int d = 0;
int e = 0;
int g = 0;
int h = 0; // for loop variable for pulse setups. make sure the loop only runs once

int letters[7] = {a, b, c, d, e, f, y};

const int trigPin = 2;
const int echoPin = 3;

long duration;
int distance;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    srand(time(0));
    delay(3000);
    FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS, MAX_MA);
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.show();
}

void loop()
{
    pulseDistance = (measureDist() / 2);

    for (h = h; h <= 7; h++)
    {
        pulse(letters[h]);
    }

    for (int i = 0; i < sizeof(letters); i++)
    {
        if (letters[i] >= NUM_LEDS)
        {
            letters[i] = 0 - (rand() % (pulseDistance * 2));
        }
    }
}

void pulse(int x)
{
    if (x < 0)
    {
        x++;
    }
    else if (x < NUM_LEDS && x >= 0)
    {
        leds[x++] = CHSV(rand() % 255, 255, 255);
    }

    FastLED.show();
    fadeall();
}

void fadeall()
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].nscale8(225);
    }
}

int measureDist()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    return distance;
}