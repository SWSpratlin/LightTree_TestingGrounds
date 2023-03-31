# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/ArrayPulse/ArrayPulse.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/ArrayPulse/ArrayPulse.ino" 2
# 3 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/ArrayPulse/ArrayPulse.ino" 2
# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/ArrayPulse/ArrayPulse.ino"

# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/ArrayPulse/ArrayPulse.ino"
int pulseDistance;

CRGB leds[150];

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
    pinMode(trigPin, 0x1);
    pinMode(echoPin, 0x0);
    srand(time(0));
    delay(3000);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 3000);
    FastLED.addLeds<WS2812B, 8, GRB>(leds, 150);
    FastLED.setBrightness(100);
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
        if (letters[i] >= 150)
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
    else if (x < 150 && x >= 0)
    {
        leds[x++] = CHSV(rand() % 255, 255, 255);
    }

    FastLED.show();
    fadeall();
}

void fadeall()
{
    for (int i = 0; i < 150; i++)
    {
        leds[i].nscale8(225);
    }
}

int measureDist()
{
    digitalWrite(trigPin, 0x0);
    delayMicroseconds(2);
    digitalWrite(trigPin, 0x1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0x0);

    duration = pulseIn(echoPin, 0x1);

    distance = duration * 0.034 / 2;

    return distance;
}
