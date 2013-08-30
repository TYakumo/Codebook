const int MAXN = 1001, MAXV = 4100; //2SAT
vector <int> adja[MAXV];
int dfn[MAXV], low[MAXV], stk[MAXV], timeStamp, top;
bool in_st[MAXV];
int group[MAXV], G;

void tarjan(int now)
{
	dfn[now] = low[now] = ++timeStamp;
	in_st[now] = true;
	stk[top++] = now;
	
	for(int i = 0; i < adja[now].size(); i++)
	{
		int nextv = adja[now][i];
		if(dfn[nextv])
		{
			if(in_st[nextv])
				low[now] = min(low[now], dfn[nextv]);
		}
		else
		{
			tarjan(nextv);
			low[now] = min(low[now], low[nextv]);
		}
	}
	
	if(dfn[now] == low[now])
	{
		++G;
		int topV;
		do{
			topV = stk[--top];
			in_st[topV] = false;
			group[topV] = G;
		}while(topV != now);
	}
}

int main()
{
	int N, V, CV;
	//the meaning of V is total number of vertex in 2SAT Graph
	//and from 0 ... (V/2)-1 are x0 ... xn
	//while V/2 ... V are neg(x0) ... neg(xn)
	//therefore, CV = V>>1;
	for(int i = 0; i < V; i++)
		adja[i].clear();
		
	top = timeStamp = G = 0;
	memset(dfn, 0, sizeof(dfn));
	memset(in_st, false, sizeof(in_st));
	for(int i = 0; i < V; i++)
		if(dfn[i] == 0)
			tarjan(i);
	
	bool chk = true;
	for(int i = 0; i < CV; i++)
		if(group[i] == group[i+CV])
		{
			chk = false;
			break;
		}
	
	printf("%s\n", chk ? "YES" : "NO" ); //if check is no, then no answer
	if(chk) //if check is yes, output answer
	{
		for(int i = 0; i < N; i++)
		{
			if(group[2*i] < group[2*i+CV]) 
				printf("x%d is false!\n", i);
			else
				printf("x%d is true!\n", i);
		}
	}
	return 0;
}