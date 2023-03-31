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

int x;
int y;

const int trigPin = 2;
const int echoPin = 3;

long duration;
int distance;

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
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

    pulse(255, 225);
    pulse2(255, 225);

    if (x >= NUM_LEDS)
    {
        x = 0;
    }

    if (y >= NUM_LEDS)
    {
        y = 0 - pulseDistance;
    }
}

void pulse2(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (x < NUM_LEDS)
    {
        leds[x++] = CHSV(255, 125, 255);
    }

    FastLED.show();
    fadeall(p);
    delay(0);
}

void pulse(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (y < 0)
    {
        y++;
    }
    else if (y < NUM_LEDS && y >= 0)
    {
        leds[y++] = CHSV(150, 255, 255);
    }

    FastLED.show();
    fadeall(p);
    delay(0);
}

void fadeall(int p)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].nscale8(p);
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