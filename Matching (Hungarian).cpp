const int MAXN = 310; //Maximum Bipartite Matching
vector <int> adja[MAXN];
int mat[MAXN], V; //V is the number of left hand side vertex
bool used[MAXN];

bool extend(int now)
{
    for(int i = 0; i < adja[now].size(); i++)
    {
        int nextn = adja[now][i];
        
        if(!used[nextn])
        {
            used[nextn] = true;
            if(mat[nextn] == -1 || extend(mat[nextn]))
            {
                mat[nextn] = now;
                return true;
            }
        }
    }
    return false;
}

int main()
{     
    int ans = 0;
    for(int i = 0; i < V; i++)
    {
        memset(used, false, sizeof(used));
        if(extend(i))
            ans++;
    }
}

