void Highhigh
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
    
    tone(speaker,melody[4]); //ソ
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
    notone(speaker);

    tone(speaker, melody[2]); //ミ
    delay(350);
    notone(speaker);

    tone(speaker, melody[3]); //ソ
    delay(350);
    noTone(speaker);

    tone(speaker, melody[4]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[5]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[4]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[4]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[7]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[4]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[3]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[2]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[1]); //ラ
    delay(450);
    notone(speaker);

     tone(speaker, melody[0]); //ラ
    delay(250);
    notone(speaker);

     tone(speaker, melody[0]); //ラ
    delay(450);
    notone(speaker);

    delay(550);
}
