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

bool spaced;

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
    spaced = false;
}

void loop()
{
    pulseDistance = (measureDist() / 2);

    pulse(255, 230);
    pulse2(255, 230);

    Serial.println(pulseDistance);

    if (x > NUM_LEDS)
    {
        x = 0;
    }

    delay(1);

    if (y >= NUM_LEDS)
    {
        y = 0 - pulseDistance;
    }
}

void pulse(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);
    if (x < 0)
    {
        x += pulseSpeed();
    }
    else if (x <= NUM_LEDS && x >= 0)
    {
        x += pulseSpeed();
        leds[x] = CRGB::Blue;
        if ((x + 1) <= NUM_LEDS)
        {
            leds[x + 1] = CHSV(150, 255, 255);
        }
    }

    FastLED.show();
    fadeall(p);
}

void pulse2(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (y < 0)
    {
        y++;
    }
    else if (y <= NUM_LEDS && y >= 0)
    {
        y += (pulseSpeed() + 2);
        leds[y] = CHSV(255, 255, 255);

        if ((y + 2) <= NUM_LEDS)
        {
            leds[y + 1] = CHSV(255, 255, 255);
            leds[y + 2] = CHSV(255, 255, 255);
        }
    }

    FastLED.show();
    fadeall(p);
}

void fadeall(int p)
{
    for (int i = 0; i < NUM_LEDS; i++)
    {
        leds[i].nscale8(p);
    }
}

int pulseSpeed()
{
    if (40 <= pulseDistance)
    {
        return 1;
    }
    if (20 <= pulseDistance <= 39)
    {
        return 2;
    }
    if (0 <= pulseDistance <= 19)
    {
        return 3;
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