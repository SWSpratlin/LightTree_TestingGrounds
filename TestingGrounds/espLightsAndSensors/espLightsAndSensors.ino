#include <Arduino.h>

uint32_t Freq = 0;

// GPIO 34 Pin 5
#define echoOne 34

// GPIO 22 Pin 36
#define echoTwo 22

// GPIO 14 Pin 12
#define triggerOne 14

// GPIO 21 Pin 22
#define triggerTwo 21

// GPIO 32 Pin 7
#define firstLedOne 32

// GPIO 33 Pin 8
#define secondLedOne 33

// GPIO 25 Pin 9
#define thirdLedOne 25

// GPIO 16 Pin 27
#define firstLedTwo 16

// GPIO 17 Pin 28
#define secondLedTwo 17

// GPIO 18 Pin 30
#define thirdLedTwo 18

int distanceOne = 0;
int distanceTwo = 0;

long durationOne = 0;
long durationTwo = 0;

int skip1 = 0;
int skip2 = 0;

void setup()
{
    // begin Serial communication
    Serial.begin(115200);

    // set up all the pins for both the sensors and the LEDs
    pinMode(echoOne, INPUT);
    pinMode(echoTwo, INPUT);
    pinMode(triggerOne, OUTPUT);
    pinMode(triggerTwo, OUTPUT);
    pinMode(firstLedOne, OUTPUT);
    pinMode(firstLedTwo, OUTPUT);
    pinMode(secondLedOne, OUTPUT);
    pinMode(secondLedTwo, OUTPUT);
    pinMode(thirdLedTwo, OUTPUT);
    pinMode(thirdLedOne, OUTPUT);

    // Print all the standard stuff
    Freq = getCpuFrequencyMhz();
    Serial.print("CPU Freq = ");
    Serial.print(Freq);
    Serial.println(" MHz");
    Freq = getXtalFrequencyMhz();
    Serial.print("XTAL Freq = ");
    Serial.print(Freq);
    Serial.println(" MHz");
    Freq = getApbFrequency();
    Serial.print("APB Freq = ");
    Serial.print(Freq);
    Serial.println(" Hz");

    digitalWrite(firstLedOne, HIGH);
    digitalWrite(secondLedOne, HIGH);
    digitalWrite(thirdLedOne, HIGH);
    digitalWrite(firstLedTwo, HIGH);
    digitalWrite(secondLedTwo, HIGH);
    digitalWrite(thirdLedTwo, HIGH);

    // delay for the boot to finish
    delay(1000);
}

void loop()
{
    // measure the distance, update distance variables.
    // Run each sensor's US function
    digitalWrite(triggerOne, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerOne, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerOne, LOW);

    // Read the delay from the echo pin
    durationOne = pulseIn(echoOne, HIGH);

    // Convert to CM
    distanceOne = durationOne * 0.034 / 2;

    Serial.print("Side One Distance: ");
    Serial.print(distanceOne);

    delay(10);

    // Run each sensor's US function
    digitalWrite(triggerTwo, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerTwo, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerTwo, LOW);

    // Read the delay from the echo pin
    durationTwo = pulseIn(echoTwo, HIGH);

    // Convert to CM
    distanceTwo = durationTwo * 0.034 / 2;

    Serial.print("    Side Two Distance: ");
    Serial.println(distanceTwo);

    // apply the metering to the LEDs on side One
    if (distanceOne >= 40)
    {
        digitalWrite(firstLedOne, HIGH);
        digitalWrite(secondLedOne, LOW);
        digitalWrite(thirdLedOne, LOW);
        delay(1);
    }
    else if (distanceOne < 40 && distanceOne >= 20)
    {
        digitalWrite(firstLedOne, HIGH);
        digitalWrite(secondLedOne, HIGH);
        digitalWrite(thirdLedOne, LOW);
        delay(1);
    }
    else
    {
        digitalWrite(firstLedOne, HIGH);
        digitalWrite(secondLedOne, HIGH);
        digitalWrite(thirdLedOne, HIGH);
        delay(1);
    }

    // apply the metering to the LEDs on Side Two
    if (distanceTwo >= 40)
    {
        digitalWrite(firstLedTwo, HIGH);
        digitalWrite(secondLedTwo, LOW);
        digitalWrite(thirdLedTwo, LOW);
        delay(1);
    }
    else if (distanceTwo < 40 && distanceTwo >= 20)
    {
        digitalWrite(firstLedTwo, HIGH);
        digitalWrite(secondLedTwo, HIGH);
        digitalWrite(thirdLedTwo, LOW);
        delay(1);
    }
    else
    {
        digitalWrite(firstLedTwo, HIGH);
        digitalWrite(secondLedTwo, HIGH);
        digitalWrite(thirdLedTwo, HIGH);
        delay(1);
    }
    delay(1);
}