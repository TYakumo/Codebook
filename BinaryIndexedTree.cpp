inline void add(int x)
{
    while(x < MAXT)
    {
        ++tVal[x];
        x += x&-x;
    }
}

inline int sum(int x)
{
    int ret = 0;
    while(x > 0)
    {
        ret += tVal[x];
        x -= x&-x;
    }
    return ret;
}