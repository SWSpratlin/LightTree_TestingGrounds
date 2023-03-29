#include <Arduino.h>
#line 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
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

#line 24 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void setup();
#line 37 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void loop();
#line 49 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void pulse2(int u, int l);
#line 71 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void pulse(int u, int l);
#line 85 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
void fadeall(int p);
#line 93 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
int measureDist();
#line 24 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
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
    measureDist();
    pulse2(255, 225);
    if (x > pulseDistance)
    {
        pulse(255, 225);
    }
    delay(1);
}

void pulse2(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (x < NUM_LEDS)
    {
        leds[x++] = CHSV(255, 125, 255);
    }
    else if (x >= NUM_LEDS && x <= (NUM_LEDS + pulseDistance))
    {
        x++;
    }
    else if (x > NUM_LEDS + pulseDistance)
    {
        x = 0;
    }

    FastLED.show();
    fadeall(p);
    delay((rand() % 10));
}

void pulse(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (y > NUM_LEDS + pulseDistance)
    {
        y = 0;
    }
    leds[y++] = CHSV(150, 255, 255);
    FastLED.show();
    fadeall(p);
    delay((rand() % 10));
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
