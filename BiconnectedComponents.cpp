const int MAXN = 50100; //Biconnected Component
vector <int> adja[MAXN];
int gcnt, top, timeStamp, dfn[MAXN], low[MAXN], depth[MAXN];
pair<int, int> stk[MAXN];
set <int> group[MAXN];
bool cut[MAXN];

void BCC(int now, int nextv)
{
    int sf, st;
    group[gcnt].clear();
    do
    {                    
        sf = stk[top-1].first, st = stk[top-1].second;
        group[gcnt].insert(sf);
        group[gcnt].insert(st);
        --top;
    }while(sf != now || st != nextv);
    ++gcnt;
}

void tarjan(int now, int parent, int d)
{
    int child = 0;
    dfn[now] = low[now] = ++timeStamp, depth[now] = d;
    
    for(int i = 0; i < adja[now].size(); i++)
    {
        int nextv = adja[now][i];
        if(nextv == parent) continue;
                
        if(dfn[nextv] == 0)
        {
            stk[top++] = make_pair(now, nextv);        
            tarjan(nextv, now, d+1);
            low[now] = min(low[now], low[nextv]);
            ++child;
            
            if( (parent != -1 && low[nextv] >= dfn[now]) || (parent == -1 && child >= 2))
            {
                cut[now] = true;
                if(parent != -1) BCC(now, nextv); //not root
            }            
            if(parent == -1) BCC(now, nextv); //root
        }     
        else if(depth[nextv] < depth[now]-1) //back edge            
        {
            stk[top++] = make_pair(now, nextv);
            low[now] = min(low[now], dfn[nextv]);
        }    
    }    
}

int main()
{
    timeStamp = 0, top = 0;
    memset(cut, false, sizeof(cut));
    memset(dfn, 0, sizeof(dfn));        
    tarjan(0, -1, 1);
}

