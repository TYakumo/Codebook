const int maxN = 4, maxSt = 50, maxP = 15; //The example of IDA* for solving 15 puzzle
int map[maxN][maxN];
const int dr[4] = {1, 0, -1, 0}, dc[4] = {0, 1, 0, -1}, opp[4] = {2, 3, 0, 1};
int tr[maxP], tc[maxP], upper;
const char name[4] = {'D', 'R', 'U', 'L'};
bool pass;

void ini()
{
    for(int i = 0; i < maxP; i++)
        tr[i] = i/4, tc[i] = i%4;
}

bool solve(const int& r) //check solvability of this tile game
{
    int line[maxN*maxN], cnt = 0, inversion = 0;
     
    for(int i = 0; i < maxN; i++)
        for(int j = 0; j < maxN; j++)
            line[cnt++] = map[i][j];
                     
    for(int i = 0; i < maxN*maxN; i++)
        if(line[i] < 15)
        {
            for(int j = i+1; j < maxN*maxN; j++)
                if(line[i] > line[j])
                    inversion++;
        }
      
    return (r&1)^(inversion&1);
}

int eval() //calculating for heuristic value
{
    int ret = 0;
    for(int i = 0; i < maxN; i++)
        for(int j = 0; j < maxN; j++)
            if(map[i][j] < 15)
               ret += abs(i-tr[ map[i][j] ]) + abs(j - tc[ map[i][j] ]);
    return ret;
}

bool valid(const int& r, const int& c)
{
    return r >= 0 && r < maxN && c >= 0 && c < maxN;
}

void IDA(int depth, int r, int c, int est, int pre)
{
     if(pass) return;
     if(est == 0)
     {
        for(int i = 0; i < depth; i++)
            printf("%c", rec[i]);
        printf("\n");
        pass = true;
        return ;
     }
               
    for(int i = 0; i < 4; i++)
        if(i != pre)
            {
                int nr = r + dr[i], nc = c + dc[i], oCost, nCost, bak;
             
                if( valid(nr, nc) )
                {
                    bak = map[nr][nc];
                    oCost = ab(nr-tr[bak]) + ab(nc-tc[bak]);
                    nCost = ab(r-tr[bak]) + ab(c-tc[bak]);
                 
                    if(depth + est + nCost - oCost + 1 <= upper )
                    {
                        map[r][c] = bak, map[nr][nc] = 15;
                        rec[depth] = name[i];
                        IDA(depth+1, nr, nc, est + nCost - oCost, opp[i]);
                        map[r][c] = 15, map[nr][nc] = bak;
                        if(pass) return;
                    }
                }
            }
}
char rec[maxSt];

int main()
{
    int T;
    scanf("%d", &T);    
    ini();
    for(int t = 0; t < T; t++)
    {
        pass = false;
        int sr, sc;
        for(int i = 0; i < maxN; i++)
            for(int j = 0; j < maxN; j++)
            {
                scanf("%d", &map[i][j]);
                if(map[i][j]) map[i][j]--;
                else          map[i][j] = 15, sr = i, sc = j;
            }
            
        if( !solve(sr) )        printf("This puzzle is not solvable.\n");  
        else
        {
            int cost = eval();
            upper = cost+5 <= maxSt ? cost+5 : maxSt;
                
            while( !pass )
            {
                IDA(0, sr, sc, cost, -1);
                upper = upper+5 <= maxSt ? upper+5 : maxSt;
            }
        }
    }    
    return 0;
}