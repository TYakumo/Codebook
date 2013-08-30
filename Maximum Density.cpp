/*
solve a problem that find a continuous cells with Maximum Density
whose length is at least F
*/
const int maxN = 100001;
long long sum[maxN];

int main()
{
    int N, F, ans;
    scanf("%d%d", &N, &F);
    
    for(int i = 1; i <= N; i++)
    {
            int temp;
            scanf("%d", &temp);
            sum[i] = sum[i-1]+temp*1000;
    }
        
    int front = 1, rear = F;
    ans = sum[F]/F;
           
    while( rear < N )
    {                  
        rear++;
        int density = (sum[rear]-sum[front-1])/(rear-front+1),
        f = rear-F+1 , nd = (sum[rear]-sum[f-1])/(rear-f+1);
                  
        if(nd >= density) front = f, density = nd;;
        ans = ans > density  ? ans : density;
    }
    
    printf("%d\n", ans);
    
    return 0;
}
