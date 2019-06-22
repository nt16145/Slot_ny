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
