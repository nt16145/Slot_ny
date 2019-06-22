#include <Wire.h>
#include <FlexiTimer2.h>
//#define STOP 0
//#define COUNT 1
#define LDaddrs1 (0x70) //HT16K33
#define LED0 5
#define LED1 6
#define LED2 10
#define LED3 11

int i1 = 0, i2 = 0, i3 = 0, i4 = 0, score = 30;

void setup()
{
  // 必要なものは後で追記していく感じで
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A0, INPUT);

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
  Wire.write(0xE);
  Wire.endTransmission();
  // Display setup
  Wire.beginTransmission(LDaddrs1);
  Wire.write(0x81);
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
    Chattering(1);
  }
  if (digitalRead(A0) == HIGH)
  {
    Number_of_times_pressed++;
    Serial.print(Number_of_times_pressed);//確認用
    Chattering(1);
  }
}
void Sseg()
{

/*  int Number_of_times_pressed = 0, //
      i_h = 0,                     //hardのループ回数
      i_n = 0,                     //normal
      i_e = 0,                     //hard
      hard_hit,
      normal_hit,
      easy_hit,
      hard_hoji,
      normal_hoji,
      easy_hoji; //難易度別のループ変数*/

  /*if (digitalRead(DIPSW2) == HIGH)
  {
    // Difficulty "HARD" ここに処理書く感じ?
    i_h = 32; //hardのループ回数
    hard_hit = random(1, 33) //hardの時の当たる回数
  }
  else if (digitalRead(DIPSW1) == HIGH)
  {
    i_n = 16;
    normal_hit = random(1, 17);
    // Difficulty "NOMAL"
  }
  else
  {
    i_e = 8;
    easy_hit = random(1, 9);
    // Difficulty "EASY"
  }*/

  const unsigned char segu[11] = {
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
  //数字をカウントす
  if (Number_of_times_pressed == 0)
  {
    i1++;
    i2++;
    i3++;
    i4++;
  }
  else if (Number_of_times_pressed == 1)
  {
    i2++;
    i3++;
    i4++;
  }
  else if (Number_of_times_pressed == 2)
  {
    i3++;
    i4++;
  }
  else if (Number_of_times_pressed == 3)
  {
    i4++;
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

void loop()
{
  Sseg();
  delay(1000);
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