//今回の進捗:1回目のあたり確定はできる、2回目以降できない
#include <Wire.h>
#include <FlexiTimer2.h>

#define LED0 5
#define LED1 6
#define LED2 10
#define LED3 11
#define DIPSW1 13
#define DIPSW2 12
#define DIPSW3 9
#define DIPSW4 8
#define speaker 7
#define LDaddrs1 (0x70) //HT16K33

int state = 0, Max = 0, ok, check[5], Stop = 0;
int i1 = 0, i2 = 0, i3 = 0, i4 = 0, score = 30;
int mode;
const unsigned char segu[] = {
    0x3F, //0
    0x06, //1
    0x5B, //2
    0x4F, //3
    0x66, //4
    0x6D, //5
    0x7D, //6
    0x27, //7
    0x7F, //8
    0x6F  //9
};
int Number_of_times_pressed = 0,
    i_h = 32, //hardのループ回数
    i_n = 16, //normal
    i_e = 8,
    hard_hit = 0,
    normal_hit = 0,
    easy_hit = 0,
    hard_hoji = 0,
    normal_hoji = 0,

    easy_hoji = 0; //hard;

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
    pinMode(A0, INPUT); //Analog
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

    FlexiTimer2::set(100, SW);
    FlexiTimer2::start();
}

void SW()
{
    if (digitalRead(A1) == HIGH)
    {
        digitalWrite(LED0, LOW);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        score = 0;
        Number_of_times_pressed = 0;
        if (mode == 1)
        {
            hard_hoji++;
        }
        else if (mode == 2)
        {
            normal_hoji++;
        }
        else if (mode == 3)
        {
            easy_hoji++;
        }
        Chattering(1);
    }
    if (digitalRead(A0) == HIGH)
    {
        Number_of_times_pressed++;
        //Serial.print(Number_of_times_pressed); //確認用
        Chattering(0);
    }
}

void set_level()
{
    if (digitalRead(DIPSW2) == HIGH)
    {
        i_h = 32; //hardのループ回数
        if (hard_hit == 0)
            hard_hit = random(1, 32);
        mode = 1; //hardの時の当たる回数
    }
    else if (digitalRead(DIPSW1) == HIGH)
    {
        i_n = 16;
        if (normal_hit == 0)
            normal_hit = random(1, 16);
        mode = 2;
        // Difficulty "NOMAL"
    }
    else
    {
        i_e = 8;
        if (easy_hit == 0)
            easy_hit = random(1, 8);
        mode = 3;
        // Difficulty "EASY"
    }
}

void Sseg()
{
    if (digitalRead(A1))
        Stop = 1;
    while (Stop == 0)
    {
        Wire.beginTransmission(LDaddrs1);
        Wire.write(0x00);
        Wire.write(segu[i1]); // Control Digit1
        Wire.write(0x00);
        Wire.write(segu[i2]); // Control Digit2
        Wire.write(0x00);
        Wire.write(0x00); // Control D1,D2,D3
        Wire.write(0x00);
        Wire.write(segu[i3]); // Control Digit3
        Wire.write(0x00);
        Wire.write(segu[i4]); // Control Digit4
        Wire.endTransmission();
        //数字をカウントする
        if (Number_of_times_pressed == 0)
        {
            i1++;
            i2++;
            i3++;
            i4++;
        }
        else if (Number_of_times_pressed == 1)
        {
            if ((mode == 1 && hard_hit == hard_hoji) || (mode == 2 && normal_hit == normal_hoji) || (mode == 3 && easy_hit == easy_hoji))
            {
                i1 = 7;
                i2++;
                i3++;
                i4++;
            }
            else
            {
                i2++;
                i3++;
                i4++;
            }
        }
        else if (Number_of_times_pressed == 2)
        {
            if ((mode == 1 && hard_hit == hard_hoji) || (mode == 2 && normal_hit == normal_hoji) || (mode == 3 && easy_hit == easy_hoji))
            {
                i1 = 7;
                i2 = 7;
                i3++;
                i4++;
            }
            else
            {
                i3++;
                i4++;
            }
        }
        else if (Number_of_times_pressed == 3)
        {
            if ((mode == 1 && hard_hit == hard_hoji) || (mode == 2 && normal_hit == normal_hoji) || (mode == 3 && easy_hit == easy_hoji))
            {
                i1 = 7;
                i2 = 7;
                i3 = 7;
                i4++;
            }
            else
            {
                i4++;
            }
        }
        else if (Number_of_times_pressed == 4)
        {
            if ((mode == 1 && hard_hit == hard_hoji) || (mode == 2 && normal_hit == normal_hoji) || (mode == 3 && easy_hit == easy_hoji))
            {
                i1 = 7;
                i2 = 7;
                i3 = 7;
                i4 = 7;
                hard_hit = 0;
                normal_hit = 0;
                easy_hit = 0;
            }
            if ((hard_hoji == i_h) || (normal_hoji == i_n) || (easy_hoji == i_e))
            {
                hard_hoji = 0;
                normal_hoji = 0;
                easy_hoji = 0;
                set_level();
            }
            score = score_check(i4, i3, i2, i1);
            if (score != 0)
            {
                Wire.beginTransmission(LDaddrs1);
                Wire.write(0x00);
                Wire.write(segu[i1]); // Control Digit1
                Wire.write(0x00);
                Wire.write(segu[i2]); // Control Digit2
                Wire.write(0x00);
                Wire.write(0x00); // Control D1,D2,D3
                Wire.write(0x00);
                Wire.write(segu[i3]); // Control Digit3
                Wire.write(0x00);
                Wire.write(segu[i4]); // Control Digit4
                Wire.endTransmission();
                if (score == 40)
                {
                    digitalWrite(LED0, HIGH);
                    digitalWrite(LED1, HIGH);
                    digitalWrite(LED2, HIGH);
                    digitalWrite(LED3, HIGH);
                    Highhigh();
                }
                if (score == 30)
                {
                    digitalWrite(LED0, HIGH);
                    digitalWrite(LED1, HIGH);
                    digitalWrite(LED2, HIGH);
                    high();
                }
                if (score == 20)
                {
                    digitalWrite(LED0, HIGH);
                    digitalWrite(LED1, HIGH);
                    low();
                }
                if (score == 10)
                {
                    digitalWrite(LED0, HIGH);
                    Lowlow();
                }
                //LED();
            }
            /*~~under~~*/
            //score_check(i1, i2, i3, i4);
        }

        if (i1 == 10)
        {
            i1 = 0;
        }
        if (i2 == 10)
        {
            i2 = 0;
        }
        if (i3 == 10)
        {
            i3 = 0;
        }
        if (i4 == 10)
        {
            i4 = 0;
        }
    }
    Stop = 0;
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
    //loop内を待機状態として作成する
    //set_level_function
    //set_level();

    //slot_machine_function
    if (digitalRead(A0))
    {
        Chattering(0);
        set_level(); //難易度別当たり回数設定
        Sseg();
    }
}

int score_check(int i4, int i3, int i2, int i1)
{
    int score, num = -1;
    if (i4 == i3 || i2 == i1)
    {
        if (i4 == i2 || i3 == i1)
        {
            if (i4 == i3 && i3 == i2)
            {
                if (i4 == 7)
                {
                    score = 40;
                    return score;
                }
                else
                {
                    score = 30;
                    return score;
                }
            }
            if ((i1 == 7 && i2 == 7 && i3 == 7) || (i1 == 7 && i2 == 7 && i4 == 7) || (i1 == 7 && i3 == 7 && i4 == 7) || (i2 == 7 && i3 == 7 && i4 == 7))
            {
                //3�R7
                score = 30;
                return score;
            }
            if (i1 - i2 + i3 - i4 == 1 || i1 - i2 + i3 - i4 == -1)
            {
                //3�R+-1
                score = 20;
                return score;
            }
            else
            {
                //3�R+-2�ȏ�
                score = 10;
                return score;
            }
        }
        else
        {
            //3�R�����ĂȂ�
            score = 0;
        }
    }
    return score;
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

void Highhigh()
{
    int melody[16] = {
        262, //ド
        294, //｜
        330, //｜
        349,
        392,
        440,
        494,
        523,
        587,
        659,
        698,
        783,
        880,
        987,
        1046,
    }; //シ

    tone(speaker, melody[4]); //ソ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[2]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[3]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[4]); //ドー
    delay(350);
    noTone(speaker);

    tone(speaker, melody[0]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[1]); //レ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[2]); //ド
    delay(250);
    noTone(speaker);

    tone(speaker, melody[3]); //レ-
    delay(350);
    noTone(speaker);

    tone(speaker, melody[4]); //ミ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[3]); //レ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[2]); //ド
    delay(250);
    noTone(speaker);

    tone(speaker, melody[1]); //ド
    delay(250);
    noTone(speaker);

    tone(speaker, melody[2]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[3]); //ソ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[5]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[3]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[2]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[1]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[0]); //ラ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[0]); //ラ
    delay(450);
    noTone(speaker);

    delay(550);
}

void high() //喜びの歌
{
    int melody[16] = {
        262, //ド
        294, //｜
        330, //｜
        349,
        392,
        440,
        494,
        523,
        587,
        659,
        698,
        783,
        880,
        987,
        1046,
    }; //シ

    tone(speaker, melody[9]);
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]);
    delay(450);
    noTone(speaker);

    tone(speaker, melody[10]);
    delay(450);
    noTone(speaker);

    tone(speaker, melody[11]); //ドー
    delay(450);
    noTone(speaker);

    tone(speaker, melody[11]); //ミ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[10]); //レ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ド
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //レ-
    delay(450);
    noTone(speaker);

    delay(250);

    tone(speaker, melody[7]); //ミ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //レ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //ド
    delay(450);

    tone(speaker, melody[9]); //ド
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[8]); //ソ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[8]); //ラ
    delay(450);
    noTone(speaker);

    delay(250);

    tone(speaker, melody[9]); //ソ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ド
    delay(450);
    noTone(speaker);

    tone(speaker, melody[10]);
    delay(450);
    noTone(speaker);

    tone(speaker, melody[11]); //ドー
    delay(450);
    noTone(speaker);

    tone(speaker, melody[11]); //ミ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[10]); //レ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ド
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //レ-
    delay(450);
    noTone(speaker);

    delay(250);

    tone(speaker, melody[7]); //ミ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //レ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //ド
    delay(450);

    tone(speaker, melody[9]); //ド
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[7]); //ソ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    delay(550);
}

void low() //とび森で蜂に刺されたときの音楽
{
    int melody[16] = {
        262,
        294,
        330,
        349,
        392,
        440,
        494,
        523,
        587,
        659,
        698,
        783,
        880,
        987,
        1046,
    };

    tone(speaker, melody[6]);
    delay(150);
    noTone(speaker);

    tone(speaker, melody[7]);
    delay(150);
    noTone(speaker);

    delay(150);

    tone(speaker, melody[4]);
    delay(250);
    noTone(speaker);

    tone(speaker, melody[7]); //ドー
    delay(450);
    noTone(speaker);

    delay(550);
}

void Lowlow() //ほたるのひかり
{
    int melody[21] = {
        131, //ド
        147, //｜
        165, //｜
        175,
        196,
        220,
        247,
        262,
        294,
        330,
        349,
        392,
        440,
        494,
        523,
        587,
        659,
        698,
        784,
        880,
        988};                 //シ
    tone(speaker, melody[4]); //ソ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[7]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[7]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[9]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[8]); //レ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[7]); //ド
    delay(350);
    noTone(speaker);

    tone(speaker, melody[8]); //レ-
    delay(350);
    noTone(speaker);

    delay(250);

    tone(speaker, melody[9]); //ミ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[8]); //レ
    delay(250);
    noTone(speaker);

    tone(speaker, melody[7]); //ド
    delay(250);

    tone(speaker, melody[7]); //ド
    delay(250);
    noTone(speaker);

    tone(speaker, melody[9]); //ミ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[11]); //ソ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[12]);
    delay(450);
    noTone(speaker);

    delay(350);

    tone(speaker, melody[12]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[11]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[8]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[9]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[5]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[5]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    noTone(speaker);

    tone(speaker, melody[7]); //ラ
    delay(450);
    noTone(speaker);

    delay(550);
}