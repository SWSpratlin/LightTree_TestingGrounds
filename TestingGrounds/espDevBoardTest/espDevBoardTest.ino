#include <arduino.h>

#define GPIO_pin 5
uint32_t Freq = 0;
int i = 0;
int a = 0;
int b = 0;
int c = 0;

void setup()
{
    pinMode(GPIO_pin, OUTPUT);
    Serial.begin(115200);
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
}

void loop()
{
    digitalWrite(GPIO_pin, 1);
    digitalWrite(GPIO_pin, 0);
    i++;
    a += c;
    b += 3;
    c += 4;
    if (i % 100 == 0)
    {
        Serial.print(a);
        Serial.print(", ");
        Serial.print(b);
        Serial.print(", ");
        Serial.print(c);
        Serial.print(", ");
        Serial.println(i);
    }
    if (i > 100000)
    {
        a = 0;
        b = 0;
        c = 0;
        i = 0;
    }
    delay(1);
}