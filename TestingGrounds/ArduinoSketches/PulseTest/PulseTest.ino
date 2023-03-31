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
int a;
int b;
int c;
int d;
int e;
int f;
int g;

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
    pulse3(255, 225);
    pulse4(255, 225);
    pulse5(255, 225);
    pulse6(255, 225);
    pulse7(255, 225);

    if (x >= NUM_LEDS)
    {
        x = 0;
    }
    if (y >= NUM_LEDS)
    {
        y = 0 - pulseDistance;
    }
    if (a >= NUM_LEDS)
    {
        a = 0 - (pulseDistance / 2);
    }
    if (b >= NUM_LEDS)
    {
        b = 0 - (pulseDistance * 2);
    }
    if (c >= NUM_LEDS)
    {
        c = 0 - (pulseDistance / 4);
    }
    if (d >= NUM_LEDS)
    {
        d = 0 - (pulseDistance + 12);
    }
    if (e >= NUM_LEDS)
    {
        e = 0 - (pulseDistance * 1.5);
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
}

void pulse3(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (a < 0)
    {
        a++;
    }
    else if (a < NUM_LEDS && a >= 0)
    {
        leds[a++] = CHSV(76, 255, 255);
    }

    FastLED.show();
    fadeall(p);
}

void pulse4(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (b < 0)
    {
        b++;
    }
    else if (b < NUM_LEDS && b >= 0)
    {
        leds[b++] = CHSV(106, 200, 150);
    }

    FastLED.show();
    fadeall(p);
}

void pulse5(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (c < 0)
    {
        c++;
    }
    else if (c < NUM_LEDS && c >= 0)
    {
        leds[c++] = CHSV(255, 255, 255);
    }

    FastLED.show();
    fadeall(p);
}

void pulse6(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (d < 0)
    {
        d++;
    }
    else if (d < NUM_LEDS && d >= 0)
    {
        leds[d++] = CHSV(40, 200, 150);
    }

    FastLED.show();
    fadeall(p);
}

void pulse7(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (e < 0)
    {
        e++;
    }
    else if (e < NUM_LEDS && e >= 0)
    {
        leds[e++] = CHSV(10, 200, 150);
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