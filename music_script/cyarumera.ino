yarumera_Time()
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
