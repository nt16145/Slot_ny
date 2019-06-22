void set_level(){
  if (digitalRead(DIPSW2) == HIGH)
  {
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
  }
}