#include <Wire.h>
#include <FlexiTimer2.h>
//#define STOP 0
//#define COUNT 1
#define LED0 5
#define LED1 6
#define LED3 11
#define DIPSW1 13
#define DIPSW2 12
#define DIPSW3 9
#define DIPSW4 8
#define speaker 7
#define LDaddrs1 (0x70) //HT16K33

int state = 0, T = 120, min3 = 0, min2 = 0, sec1 = 1, sec0 = 0, Max = 0, ok, check[5], light = 0;
//stateは状態、Tはカウント用秒数、minとsecは表示用の時間

void setup()
{
    // 必要なものは後で追記していく感じで
    pinMode(LED0, OUTPUT);
    pinMode(LED1, OUTPUT);
    pinMode(LED3, OUTPUT);
    pinMode(speaker, OUTPUT);
    pinMode(DIPSW1, INPUT);
    pinMode(DIPSW2, INPUT);
    pinMode(DIPSW3, INPUT);
    pinMode(DIPSW4, INPUT);
    pinMode(A0, INPUT);
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

    FlexiTimer2::set(1000, LED);
    FlexiTimer2::start();
}

// 下に関数書いていく感じ↓↓↓
void LED()
{
    switch (light)
    {
    case 0:
        digitalWrite(LED0, HIGH);
        light = 1;
        break;
    case 1:
        digitalWrite(LED0, LOW);
        light = 0;
        break;
    }
}

void Timer()
{
    int i, count = 19, ten_count = 0;
    delay(950);
    while (1)
    {
        if (min2 == 0 && sec1 == 0 && sec0 == 0)
        {
            cyarumera_Time();
            break;
        }
        delay(50);
        count++;
        if (count == 20)
        {
            if (sec0 == 0 && sec1 == 0)
            {
                min2--;
            }
            if (sec0 == 0)
            {
                sec0 = 10;
                sec1--;
            }
            if (sec1 < 0)
            {
                sec1 = 5;
            }
            if (min2 == 9)
            {
                min3 = 0;
            }
            sec0--;
            T--;
            //count++;
            Sseg();
            if (min2 == 0 && sec1 == 0 && sec0 == 0)
            { //「00:00」の場合
                min3 = 0;
                min2 = 0;
                sec1 = 0;
                sec0 = 0;
                cyarumera_Time();
                break; //カウント止める所に行って欲しい
            }
            ten_count++;
            count = 0;
        }
        if (ten_count % 10 == 0)
        {
            if (count == 0 || count == 10)
                digitalWrite(LED3, HIGH);
            if (count == 5 || count == 15)
                digitalWrite(LED3, LOW);
        }
        if (digitalRead(A0) == HIGH)
        {
            state = 0;
            Chattering(0); //チャタリング防止処理関数
            break;
        }
    }
}

void cal()
{
    int sur = 0;
    min2 = T / 60;
    sur = T % 60;
    sec1 = sur / 10;
    sec0 = sur % 10;
    if (T == 600)
        Max = 1;
}

void Sseg()
{
    const unsigned char segu[11] = {
        0x3F, //0
        0x06, //1
        0x5B, //2
        0x4F, //3
        0x66, //4
        0x6D, //5
        0x7D, //6
        0x27, //7
        0x7F, //8f
        0x6F  //9
    };
    if (Max == 1)
    {
        Wire.beginTransmission(LDaddrs1);
        Wire.write(0x00);
        Wire.write(0x06); // Control Digit1
        Wire.write(0x00);
        Wire.write(0x3F); // Control Digit2
        Wire.write(0x00);
        Wire.write(0x03); // Control D1,D2,D3
        Wire.write(0x00);
        Wire.write(0x3F); // Control Digit3
        Wire.write(0x00);
        Wire.write(0x3F); // Control Digit4
        Wire.endTransmission();
    }

    else
    {
        Wire.beginTransmission(LDaddrs1);
        Wire.write(0x00);
        Wire.write(0x00); // Control Digit1
        Wire.write(0x00);
        Wire.write(segu[min2]); // Control Digit2
        Wire.write(0x00);
        Wire.write(0x03); // Control D1,D2,D3
        Wire.write(0x00);
        Wire.write(segu[sec1]); // Control Digit3
        Wire.write(0x00);
        Wire.write(segu[sec0]); // Control Digit4
        Wire.endTransmission();
    }
    Max = 0;
}

void cyarumera_Time()
{
    int keep_cyarumera = 0;
    while (keep_cyarumera != 3)
    {
        tone(speaker, 523); //ソ
        digitalWrite(LED3, HIGH);
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        tone(speaker, 587); //ラ
        delay(250);
        digitalWrite(LED3, HIGH);
        noTone(speaker);

        tone(speaker, 659); //シ
        delay(250);
        digitalWrite(LED3, LOW);
        delay(250);
        digitalWrite(LED3, HIGH);
        delay(250);
        noTone(speaker);

        tone(speaker, 587); //ラ
        digitalWrite(LED3, LOW);
        delay(250);
        digitalWrite(LED3, HIGH);
        noTone(speaker);

        tone(speaker, 523); //ソ
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        delay(250);
        digitalWrite(LED3, HIGH);

        tone(speaker, 523); //ソ
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        tone(speaker, 587); //ラ
        delay(250);
        digitalWrite(LED3, HIGH);
        noTone(speaker);

        tone(speaker, 659); //シ
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        tone(speaker, 587); //ラ
        delay(250);
        digitalWrite(LED3, HIGH);
        noTone(speaker);

        tone(speaker, 523); //ソ
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        tone(speaker, 587); //ラ
        delay(250);
        digitalWrite(LED3, HIGH);
        delay(250);
        digitalWrite(LED3, LOW);
        delay(250);
        digitalWrite(LED3, HIGH);
        delay(250);
        digitalWrite(LED3, LOW);
        noTone(speaker);

        delay(250);
        digitalWrite(LED3, HIGH);
        delay(250);
        digitalWrite(LED3, LOW);
        delay(250);

        keep_cyarumera++;
    }
}

void set_time()
{
    int DIPSW_port[] = {DIPSW1, DIPSW2, DIPSW3};
    int i, set_up_time[] = {1, 10, 30};
    if ((digitalRead(DIPSW4) == HIGH && T == 600) || (digitalRead(DIPSW4) == LOW && T == 0))
    {
        Wire.beginTransmission(LDaddrs1);
        Wire.write(0x00);
        Wire.write(0x00); // Control Digit1
        Wire.write(0x00);
        Wire.write(0x00); // Control Digit2
        Wire.write(0x00);
        Wire.write(0x00); // Control D1,D2,D3
        Wire.write(0x00);
        Wire.write(0x00); // Control Digit3
        Wire.write(0x00);
        Wire.write(0x00); // Control Digit4
        Wire.endTransmission();
        delay(250);
        Sseg();
    }
    if (digitalRead(DIPSW4) == HIGH)
    {
        for (i = 2; i >= 0; i--)
        {
            if (digitalRead(DIPSW_port[i]) == HIGH)
            {
                T += set_up_time[i];
                break;
            }
        }
        if (T > 600)
            T = 600;
    }
    else
    {
        for (i = 2; i >= 0; i--)
        {
            if (digitalRead(DIPSW_port[i]) == HIGH)
            {
                T -= set_up_time[i];
                break;
            }
        }
        if (T < 0)
            T = 0;
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
    switch (state)
    {
    case 0:
        cal();
        Sseg();
        Serial.println("OK");
        if (digitalRead(A0) == HIGH)
        {
            digitalWrite(LED1, LOW);
            state = 1;
            Chattering(1); //チャタリング防止処理関数
            break;
        }
        if (digitalRead(A1) == HIGH)
        {
            digitalWrite(LED1, HIGH);
            set_time();    //時間設定用関数 (set_time)
            Chattering(1); //チャタリング防止処理関数
        }
        break;
    case 1:
        Timer(); //Timer関数 & Sseg関数
        state = 0;
        break;
    }
}
