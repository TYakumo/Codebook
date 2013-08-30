//Solving a classic problem of Optimal Binary Search Tree in O(N^2)
//Where p i is the number of times searching key i
//And q j is the number of times searching a key which is miss and < p j+1
const int MAXN = 101+1, inf = 2000000000;
int DP[MAXN][MAXN], p[MAXN], q[MAXN], sum[2][MAXN], r[MAXN][MAXN];

int main()
{
    int N, T = 0;
    
    while(scanf("%d", &N)==1)
    {
        for(int i = 1; i <= N; i++)
        {
            scanf("%d", &p[i]);
            sum[0][i] = sum[0][i-1]+p[i];
        }
           
        for(int i = 0; i <= N; i++)
        {
            scanf("%d", &q[i]);            
            if(i) sum[1][i] = sum[1][i-1]+q[i];
            else sum[1][i] = q[i];
        }
        
        for(int i = 1; i <= N+1; i++)
            DP[i][i-1] = q[i-1];
        
        for(int i = 0; i <= N; i++)
            r[i][i] = i, r[i+1][i] = i+1;
        
        for(int l = 1; l <= N; l++)
            for(int i = 1; i+l-1 <= N; i++)
            {
                int j = i+l-1, nc;
                DP[i][j] = inf;
                
                for(int k = r[i][j-1]; k <= r[i+1][j]; k++)
                {
                    nc = DP[i][k-1] + DP[k+1][j] + sum[0][j]-sum[0][i-1] + sum[1][j]-sum[1][i-1]+q[i-1];
                    
                    if(nc <= DP[i][j])
                        DP[i][j] = nc, r[i][j] = k;
                }
            }
        
        printf("Test Case %d: %d\n", ++T, DP[1][N]-sum[1][N]);
    }
    
    return 0;
}
