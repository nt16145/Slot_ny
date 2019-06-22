#include <Wire.h>
#include <FlexiTimer2.h>
//#define STOP 0
//#define COUNT 1
#define LED0 5
#define LED1 6
#define LED2 10
#define LED3 11
#define LDaddrs1 (0x70) //HT16K33

int score = 30;

void setup()
{
    // 必要なものは後で追記していく感じで
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED2, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(A1, INPUT);

    Wire.begin();
    Wire.setClock(400000L);
    // system oscillator on
    Wire.beginTransmission(LDaddrs1);
    Wire.write(0x21);
    Wire.endTransmission();
    // ROW/INT output is set to ROW driver output
    Wire.beginTransmission(LDaddrs1);
    Wire.write(0xA0);
    Wire.endTransmission();
    // Dimming
    Wire.beginTransmission(LDaddrs1);
    Wire.write(0b11101111);
    Wire.endTransmission();
    // Display setup
    Wire.beginTransmission(LDaddrs1);
    Wire.write(0b10000001);
    Wire.endTransmission();

    FlexiTimer2::set(100, SW1);
    FlexiTimer2::start();
}
void SW1()
{
    if (digitalRead(A1) == HIGH)
    {
        //LEDを消灯する
        digitalWrite(LED0, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        score = 0;
        Chattering(1);
    }
}

void LED()
{
    if (score == 10)
    {
        digitalWrite(LED0, HIGH);
    }
    if (score == 20)
    {
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, HIGH);
    }
    if (score == 30)
    {
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
    }
    if (score == 40)
    {
        digitalWrite(LED0, HIGH);
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
    }
}

void Chattering(int port)
{
    int cha = 0;
    while (cha < 15)
    {
        if (analogRead(port) <= 1020)
        {
            cha++;
        }
        else
        {
            cha = 0;
        }
        delay(1);
    }
}

void loop()
{
    LED();
}