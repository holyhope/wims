package atp;


class BoxC
{

    public BoxC(int i, int j, int k)
    {
        dx = i;
        dy_pos = j;
        dy_neg = k;
    }

    public BoxC()
    {
        dx = 0;
        dy_pos = 0;
        dy_neg = 0;
    }

    public int dx;
    public int dy_pos;
    public int dy_neg;
}
