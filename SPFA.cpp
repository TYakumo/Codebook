#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
using namespace std;

struct hole
{
    long long t;
    pair <int, int> dest;
};

const int dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
const int MAXN = 31, MAXQ = MAXN*MAXN, inf = 100000000;
int cnt[MAXN][MAXN], mmap[MAXN][MAXN];
long long dis[MAXN][MAXN];
bool in_que[MAXN][MAXN];
hole holes[MAXN][MAXN];
int R, C, G, E, front, rear;
pair <int, int> que[MAXQ];

bool valid(int r, int c)
{
    return r >= 0 && r < R && c >= 0 && c < C;
}

void update(const int& r, const int& c, long long cost, int cc)
{
    if(cost < dis[r][c])
    {
        dis[r][c] = cost;
        cnt[r][c] = cc+1;
        
        if(!in_que[r][c])
        {
            in_que[r][c] = true;
            que[rear] = make_pair(r, c);
            rear = (rear+1)%MAXQ;
        }
    }
}

int main()
{
    while(scanf("%d%d", &R, &C) && R)
    {
        //load and construct map
        memset(mmap, 0, sizeof(mmap));
        scanf("%d", &G);
        for(int i = 0; i < G; i++)
        {
            int r, c;
            scanf("%d %d", &r, &c);
            mmap[r][c] = 2;
        }
        
        E = R*C-1;
        scanf("%d", &G);
        for(int i = 0; i < G; i++)
        {
            int sx, sy, dx, dy, dt;
            scanf("%d %d %d %d %d", &sx, &sy, &dx, &dy, &dt);
            mmap[sx][sy] = 1;
            holes[sx][sy].dest = make_pair(dx, dy), holes[sx][sy].t = dt;
        }
        
        //SPFA
        memset(cnt, 0, sizeof(cnt));
        memset(in_que, false, sizeof(in_que));
        for(int i = 0; i < R; i++)
            for(int j = 0; j < C; j++)
                dis[i][j] = inf;
                
        dis[0][0] = 0;
        
        bool negcyc = false;
        que[0] = make_pair(0,0), front = 0, rear = 1;
        
        while(front != rear)
        {
            if(negcyc) break;
            int nr = que[front].first, nc = que[front].second;            
            in_que[nr][nc] = false;   
                
            if(nr==R-1&& nc==C-1)
            {
                front = (front+1)%MAXQ;
                continue;
            }
            
            if(mmap[nr][nc] == 1)
            {
                const pair <int, int> & tempq = holes[nr][nc].dest;
                update(tempq.first, tempq.second, dis[nr][nc]+holes[nr][nc].t, cnt[nr][nc]);
                if(cnt[tempq.first][tempq.second] > E) negcyc = true;
                front = (front+1)%MAXQ;
                continue;
            }
            
            for(int i = 0; i < 4 && !negcyc; i++)
            {
                int newr = nr+dr[i], newc = nc+dc[i];
                long long cost = dis[nr][nc]+1;
                if(valid(newr, newc) && mmap[newr][newc] != 2)
                {
                        update(newr, newc, cost, cnt[nr][nc]);
                        if(cnt[newr][newc] > E) negcyc = true;
                }
            }        
            
            front = (front+1)%MAXQ;
        }
        
        if(negcyc) printf("Never\n");
        else if(dis[R-1][C-1] < inf) printf("%lld\n", dis[R-1][C-1]);
        else printf("Impossible\n");
    }
    
    return 0;
}

