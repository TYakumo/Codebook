//Convex Hull : Save the original point set in p
//and after finishing the andrew's monotone chain
//CH will become a convex hull which is what we want
const int maxP = 10001;
struct point{ double x, y; };
point p[maxP], CH[maxP];

double cross(const point& a, const point& b, const point& c)
{
       return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); 
}

bool cmp(const point& a, const point& b)
{
     return a.x<b.x || (a.x==b.x && a.y<b.y);
}

int main()
{
    int N, cnt = 0;
    
    while( scanf("%d", &N) && N )
    {                              
        sort(p, p+N, cmp);           
        int m = 0;       		
        for(int i = 0; i < N; i++)
        {
            while( m>=2 && cross(CH[m-2], CH[m-1], p[i]) <= 0 ) m--;
            CH[m++] = p[i];
        }
           
        for(int i = N-2, t = m+1; i >= 0; i--)
        {
            while( m>=t && cross(CH[m-2], CH[m-1], p[i]) <= 0 ) m--;
            CH[m++] = p[i];
        }
    }    
    return 0;
}
