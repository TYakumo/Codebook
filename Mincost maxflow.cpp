const int maxN = 101, maxQ = maxN*2+2, inf = 2000000; //Mincost Maxflow

int cap[maxQ][maxQ], cost[maxQ][maxQ], dis[maxQ];
int front, rear, source, sink;
int N, M, ans, queue[maxQ], path[maxQ], upperCap[maxQ];
bool in_queue[maxQ];

inline bool minCostMaxFlow()
{
     front =  0, rear = 1;
     memset(in_queue, false, sizeof(in_queue));
     for(int i = 0; i <= sink; i++)
             dis[i] = inf;
     dis[source] = 0;
     queue[0] = source, in_queue[source] = true, upperCap[source] = inf;
     
    while( front != rear )
    {
        int now = queue[front];
        in_queue[now] = false;
            
        for(int i = 0; i <= sink; i++)
            if(cap[now][i])
            {
                int nCost = dis[now]+cost[now][i];                                   
                if(nCost < dis[i])
                {
                    dis[i] = nCost, path[i] = now;
                    upperCap[i] = min(upperCap[now], cap[now][i]);
                                            
                    if( !in_queue[i] )
                    {
                        in_queue[i] = true;
                        queue[rear] = i;
                        rear = (rear+1) % maxQ;
                    }
                }        
            }
            
        front = (front+1) % maxQ;
     }
     if(dis[sink] == inf) return false;
     
     //reversing flow     
     int now = sink, pre = path[sink], cc = upperCap[sink];
     ans += dis[sink];     
     do
     {
            cap[ pre ][ now ] -= cc;
            cap[ now ][ pre ] += cc;
            now = pre, pre = path[now];
     }while( now != source );
     
     return true;
}

int mincostMaxflowAns()
{
	ans = 0;
	while( MinCostMaxFlow() ); 
}
