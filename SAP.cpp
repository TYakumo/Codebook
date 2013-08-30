const int MAXN = 200, MAXV = MAXN*2+20, INF = 100000; //Improve SAP, Max flow
struct edge
{
	int to, cap, cp;
	edge() {}
	edge(int tt, int ccap, int ccp) : to(tt), cap(ccap), cp(ccp) { }
};


int src = 0, sink, V;
vector <edge> adja[MAXV];
int dist[MAXV], num[MAXV];

void addEdge(int f, int t, int c)
{
    adja[f].push_back( edge(t, c, adja[t].size()) );
    adja[t].push_back( edge(f, 0, adja[f].size()-1) );
    radja[t].push_back(f);
}

int aug(int now, int leftCap)
{
    if(now == sink) return leftCap;
    
    int remainCap = leftCap, minDist = V;
    for(int i = 0; i < adja[now].size(); i++)
    {
        int nextv = adja[now][i].to;
        if(adja[now][i].cap && dist[now] == dist[nextv]+1)
        {
            int flow = aug(nextv, min(remainCap, adja[now][i].cap));
            adja[now][i].cap -= flow;
            remainCap -= flow;
            adja[nextv][ adja[now][i].cp ].cap += flow;
            
            if (dist[src] == V || remainCap == 0) return leftCap-remainCap;  
        }
    }
    
    if(dist[src] == V) return leftCap-remainCap;    
    
    if(remainCap == leftCap)
    {
        for(int i = 0; i < adja[now].size(); i++)
            if(adja[now][i].cap)
                minDist = min(minDist, dist[ adja[now][i].to ]+1);
                
        if(--num[ dist[now] ])
            ++num[ dist[now] = minDist ];
        else
            dist[src] = V;
    }
    return leftCap-remainCap;    
}

int sap()
{
    memset(dist, 0, sizeof(dist));
    memset(num, 0, sizeof(num));
    num[0] = V;    
        
    int ret = 0;
    while(dist[src] < V)
        ret += aug(src, INF);    
    
    return ret;
}
