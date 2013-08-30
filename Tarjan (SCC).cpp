#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1011;
int dfn[MAXN], low[MAXN], run[MAXN], in_stack[MAXN], st[MAXN], top, round = 1, timest, ans;
vector <int> adja[MAXN];

void tarjan(int now)
{
    dfn[now] = low[now] = ++timest;
    run[now] = round;
    st[top++] = now;
    
    for(int i = 0; i < adja[now].size(); i++)
    {
        int nextn = adja[now][i];
        if(run[nextn] != round) //white
        {
            tarjan(nextn);
            low[now] = low[now] < low[nextn] ? low[now] : low[nextn];
        }
        else if(in_stack[nextn] != round) //gray
            low[now] = low[now] < dfn[nextn] ? low[now] : dfn[nextn];
    }
       
    if(low[now] == dfn[now])
    {
        ans++;        
        do{ in_stack[st[--top]] = round; }while(low[st[top]] != dfn[st[top]]);
    }
}

int main()
{
    int T, N, M;
    scanf("%d", &T);
    
    while(T--)
    {
        int f, t;
        scanf("%d%d", &N, &M);
        
        for(int i = 0; i < N; i++)
            adja[i].clear();
                
        while(M--)
        {
            scanf("%d%d", &f, &t);
            f--, t--;
            adja[f].push_back(t);
        }
        
        timest = ans = top = 0;        
        for(int i = 0; i < N; i++)
            if(run[i] != round)
                tarjan(i);
            
        round++;        
        printf("%d\n", ans);        
        scanf("%d", &M); //clear
    }
    
    return 0;
}

