void low() //とび森で蜂に刺されたときの音楽
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
        659,　//ミ　９
        698,
        783,
        880,
        987,
        1046,
    }; //シ

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
