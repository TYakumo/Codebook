#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

struct floe
{
    int x, y;
};

const int MAXV = 203, inf = 2000;
int height[MAXV], excess[MAXV], ocf[MAXV][MAXV], cf[MAXV][MAXV], total; //index src 0, in -> 1 ... N, out N+1 ... 2N, sink 2N+1
int N, V, T, src, sink;
double D;
vector <int> adja[MAXV], ans;
floe floes[MAXV];

inline int mmin(int a, int b)
{
    return a < b ? a : b;
}

inline void pushflow(const int& f, const int& t)
{
    int lower = mmin(excess[f], cf[f][t]);
    excess[f] -= lower, excess[t] += lower;
    cf[f][t] -= lower, cf[t][f] += lower;
}

inline void relabel(const int & n)
{
    height[n] = inf;
    for(int i = 0; i < adja[n].size(); i++)
        if(cf[n][adja[n][i]])
            height[n] = mmin(height[n], height[adja[n][i]]);
    height[n]++;
}

bool flowtry(int n)
{
    memset(height, 0, sizeof(height));
    memset(excess, 0, sizeof(excess));
    memcpy(cf, ocf, sizeof(cf));
    height[src] = V;
    cf[n+1][sink] = total;
        
    //ini the excess flow    
    vector <int> act;
    for(int i = 0; i < adja[src].size(); i++)
    {
        int nextn = adja[src][i], flowc = cf[src][adja[src][i]];
        excess[nextn] = flowc;
        cf[nextn][src] = flowc;
        cf[src][nextn] = 0;
        act.push_back(nextn);
    }
    
    //push relabel
    while(act.size())
    {
        int themax = -1, tindex, now;
        for(int i = 0; i < act.size(); i++)
            if(height[act[i]] > themax)
                tindex = i, themax = height[act[i]];
        
        now = act[tindex];
        act[tindex] = act.back();
        act.pop_back();
        
        //discharge
        while(excess[now])
        {
            relabel(now);
            
            for(int i = 0; i < adja[now].size(); i++)
            {
                int nextn = adja[now][i];
                if(cf[now][nextn] && height[now] == height[nextn]+1)
                {
                    if(nextn != src && nextn != sink && excess[nextn] == 0) act.push_back(nextn);
                    pushflow(now, nextn);
                }                   
                if(excess[now] == 0) break;
            }
        }
    }
    
    return excess[sink] == total;
}

int main()
{
    scanf("%d", &T);
    
    while(T--)
    {
        scanf("%d %lf", &N, &D);
        D = D*D;
        V = 2*N+2, src = 0, sink = V-1;
        //initialization for max flow
        for(int i = 0; i < V; i++)
            adja[i].clear();
        
        ans.clear();    
        memset(ocf, 0, sizeof(ocf));
        total = 0;
        
        for(int i = 0; i < N; i++)
        {
            int cc, ccap;
            adja[src].push_back(i+1);
            adja[i+1].push_back(src);
            adja[i+1].push_back(i+1+N); //self connected
            adja[i+1+N].push_back(i+1);
            adja[sink].push_back(i+1);//everybody to the sink
            adja[i+1].push_back(sink);
            scanf("%d %d %d %d", &floes[i].x, &floes[i].y, &cc, &ccap);
            
            total += cc;
            ocf[src][i+1] = cc, ocf[i+1][i+1+N] = ccap;
        }
        
        
        for(int i = 0; i < N; i++)
            for(int j = i+1; j < N; j++)
            {
                double dx = (floes[i].x-floes[j].x), dy = (floes[i].y-floes[j].y), dis = dx*dx+dy*dy;
                
                if(dis <= D) //create a capacity
                {
                    adja[i+1+N].push_back(j+1);
                    adja[j+1+N].push_back(i+1);
                    adja[j+1].push_back(i+1+N);
                    adja[i+1].push_back(j+1+N);
                    ocf[i+1+N][j+1] = ocf[j+1+N][i+1] = inf;
                }
            }
        
        //solution
        //enumerate all ending points
        for(int i = 0; i < N; i++)
            if(flowtry(i))
                ans.push_back(i);
        
        //print out
        for(int i = 0; i < ans.size(); i++)
        {
            if(i) putchar(' ');
            printf("%d", ans[i]);
        }
        
        if(ans.size() == 0) printf("-1");
        printf("\n");
    }
        
    return 0;
}

