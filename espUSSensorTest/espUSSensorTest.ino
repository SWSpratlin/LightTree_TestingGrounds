#include <Arduino.h>

#define triggerPin 14
#define echoPin 13

uint32_t Freq = 0;

int distance = 0;
int ledSkipNumber = 0;
long duration = 0;

void setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(115200);
}

void loop()
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm");

    ledSkipNumber = headSkip(distance);

    Serial.print("   Skip Distance: ");
    Serial.println(ledSkipNumber);

    delay(50);
}

int headSkip(int &distance)
{
    // translate Sensor reading into headskip scale
    if (40 <= distance)
    {
        return 1;
    }
    else if (20 <= distance && distance < 40)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}