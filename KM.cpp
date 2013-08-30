const int MAXN = 210, inf = 200000000; //KM Algorithm
int cost[MAXN][MAXN];
int lx[MAXN], ly[MAXN], mat[MAXN], slack[MAXN];
bool sx[MAXN], sy[MAXN];
int N;

bool extend(int now)
{
    sx[now] = true;
    int temp;

    for(int i = 0; i < N; i++)
        if(!sy[i])
        {
            temp = -(cost[now][i]-lx[now]-ly[i]);

            if(temp==0)
            {
                sy[i] = true;
                if(mat[i]==-1 || extend(mat[i]))
                {
                    mat[i] = now;
                    return true;
                }
            }
            else if(temp < slack[i])
                slack[i] = temp;
        }

        return false;
}

int KM() //finding the maximum value of perfect matching
{
    int ret = 0;
    memset(lx, 0, sizeof(lx));
    memset(ly, 0, sizeof(ly));
    memset(mat, -1, sizeof(mat));
    //matching precalculation
    for(int i = 0; i < N; i++)
    {
        lx[i] = -inf;
        for(int j = 0; j < N; j++)
            lx[i] = max(lx[i], cost[i][j]);
    }
    //KM
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
            slack[j] = inf;

        while(true)
        {
            memset(sx, false, sizeof(sx));
            memset(sy, false, sizeof(sy));

            if(extend(i)) break;
            int themin = inf+1;

            for(int j = 0; j < N; j++)
                if(!sy[j] && slack[j] < themin)
                    themin = slack[j];

            for(int j = 0; j < N; j++)
            {
                if(sx[j]) lx[j] -= themin;
                if(sy[j]) ly[j] += themin;
                else slack[j] -= themin;
            }
        }
    }

    for(int i = 0; i < N; i++)
        ret += cost[mat[i]][i];
    return ret;
}
