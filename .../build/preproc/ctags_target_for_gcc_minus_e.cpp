# 1 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/VarSpeed/VarSpeed.ino"
# 2 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/VarSpeed/VarSpeed.ino" 2
# 3 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/VarSpeed/VarSpeed.ino" 2
# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/VarSpeed/VarSpeed.ino"

# 11 "/Users/spenserspratlin/Documents/GitHub/LightTree_TestingGrounds/TestingGrounds/ArduinoSketches/VarSpeed/VarSpeed.ino"
int pulseDistance;
int speed;

CRGB leds[150];

int x;
int y;

const int trigPin = 2;
const int echoPin = 3;

long duration;
int distance;

bool spaced;

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
    spaced = false;
}

void loop()
{
    pulseDistance = (measureDist() / 2);

    pulse(255, 230);
    pulse2(255, 230);

    Serial.println(pulseDistance);

    if (x > 150)
    {
        x = 0;
    }

    delay(1);

    if (y >= 150)
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
    else if (x <= 150 && x >= 0)
    {
        x += pulseSpeed();
        leds[x] = CHSV(150, 255, 255);
        if ((x + 1) <= 150)
        {
            leds[x + 1] = CHSV(150, 255, 255);
        }
        else
        {
            x = 0;
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
        y += pulseSpeed();
    }
    else if (y < 150 && y >= 0)
    {
        y += (pulseSpeed() + 1);
        leds[y] = CHSV(255, 255, 255);

        if ((y + 2) <= 150)
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
    for (int i = 0; i < 150; i++)
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
    digitalWrite(trigPin, 0x0);
    delayMicroseconds(2);
    digitalWrite(trigPin, 0x1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0x0);

    duration = pulseIn(echoPin, 0x1);

    distance = duration * 0.034 / 2;

    return distance;
}
