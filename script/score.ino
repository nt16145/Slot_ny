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
                    //�S��7
                    score = 40;
                    return score;
                }
                else
                {
                    //4�R����(7�ȊO)
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