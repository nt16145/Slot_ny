void slot_machine
{
    //めっちゃ楽じゃね?
    if(digitalRead(DIPSW2) == HIGH){
        // Difficulty "HARD" ここに処理書く感じ?
    }else if(digitalRead(DIPSW1) == HIGH){
        // Difficulty "NOMAL"
    }else{
        // Difficulty "EASY"
    }
}