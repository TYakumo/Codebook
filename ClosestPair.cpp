#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const int maxN = 10001;
struct point{ double x, y; };
double ab(double n) { if(n < 0) return -n; return n; }
double dis(const point& a, const point& b){ double dx = a.x-b.x, dy = a.y-b.y; return sqrt(dx*dx+dy*dy); }
bool cmpX(const point& a, const point& b){ return a.x < b.x; }
bool cmpY(const point& a, const point& b){ return a.y < b.y; }

point p[maxN], bufferP[maxN];

double closet(int low, int upper)
{
       if(upper-low<3)
       {
            double ret = dis(p[low], p[low+1]), res;
            
            if(upper-low == 2) //avoiding only two points
            {
                res = dis(p[low], p[low+2]);
                ret = ret < res ? ret : res;
                res = dis(p[low+1], p[low+2]);
                ret = ret < res ? ret : res;
            }
            return ret;           
       }
       else
       {
            //Divide and Conquer
            int mid = (low+upper)>>1, cnt = 0;
            double lr, rr, ret;
            lr = closet(low, mid);
            rr = closet(mid+1, upper);
            ret = min(lr, rr);
            
            //Middle condition
            for(int i = low; i <= mid; i++)
                if( ab(p[i].x-p[mid].x) <= ret )
                    bufferP[cnt++] = p[i];
            
            for(int i = mid+1; i <= upper; i++)
                if( ab(p[i].x-p[mid+1].x) <= ret )
                    bufferP[cnt++] = p[i];
            
            sort(bufferP, bufferP+cnt, cmpY);
            
            for(int i = 0; i < cnt; i++)
            {
                int pCnt = 0;
                for(int j = i+1; pCnt < 7 && j < cnt; j++)
                {
                    double res = dis(bufferP[i], bufferP[j]);
                    ret = ret < res ? ret : res, pCnt++;
                }
            }
            
            return ret;
       }
}

int main()
{
    int N;
    
    while( scanf("%d", &N) && N )
    {
           for(int i = 0; i < N; i++)
                   scanf("%lf%lf", &p[i].x, &p[i].y);
                                   
           sort(p, p+N, cmpX);
           
           double res = closet(0, N-1);
           
           if(res < 10000 && N > 1) printf("%.4lf\n", res);
           else             printf("INFINITY\n");
    }
    return 0;
}

