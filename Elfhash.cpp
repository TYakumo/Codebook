
int hasher(char *k)
{
	unsigned int h=0,g;
	while(*k)
	{
	    h=(h<<4)+*k++;
        g=h &0xf0000000L;
        if(g) h^=g>>24;
        h&=~g;
    }
    return h;
}