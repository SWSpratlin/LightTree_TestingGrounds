# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino" 2
# 3 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino" 2
# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"

# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/PulseTest/PulseTest.ino"
int pulseDistance;

CRGB leds[150];

int x;
int y;

const int trigPin = 2;
const int echoPin = 3;

long duration;
int distance;

void setup()
{
    pinMode(trigPin, 0x1);
    pinMode(echoPin, 0x0);
    Serial.begin(9600);
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

    pulse(255, 225);
    pulse2(255, 225);

    // if (x > pulseDistance)
    // {

    // }

    if (x >= 150)
    {
        x = 0;
    }

    if (y >= 150)
    {
        y = 0 - pulseDistance;
    }
}

void pulse2(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    if (x < 150)
    {
        leds[x++] = CHSV(255, 125, 255);
    }
    // else if (x >= NUM_LEDS && x <= (NUM_LEDS + pulseDistance))
    // {
    //     x++;
    // }
    // else if (x > NUM_LEDS + pulseDistance)
    // {
    //     x = 0;
    // }

    FastLED.show();
    fadeall(p);
    delay(0);
}

void pulse(int u, int l)
{
    int p = (rand() % (u - l + 1) + l);

    // if (y > NUM_LEDS + pulseDistance)
    // {
    //     y = 0;
    // }

    if (y < 0)
    {
        y++;
    }
    else if (y < 150 && y >= 0)
    {
        leds[y++] = CHSV(150, 255, 255);
    }

    FastLED.show();
    fadeall(p);
    delay(0);
}

void fadeall(int p)
{
    for (int i = 0; i < 150; i++)
    {
        leds[i].nscale8(p);
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
