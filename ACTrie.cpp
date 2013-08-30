//AC Trie
//Runs in O(T + sigma Pi)
const int MAXS = 5100100, MAXN = 260, MAXP = 1010, MAXT = MAXP*MAXN;
int T, Q;
char text[MAXS], str[MAXS], pattern[MAXN][MAXP];

struct actrie
{
	actrie *flink, *next[26]; //failure link, trie structure
	int pcnt;
	actrie()
	{
		flink = NULL, pcnt = 0;
		memset(next, 0, sizeof(next));
	}
};

actrie *root, *que[MAXN*MAXP];

void addPattern(char *P, int num)
{
	actrie *now = root;
	for(int i = 0; P[i]; i++)
	{
		if(now->next[ P[i] - 'A' ] == NULL) now->next[ P[i] - 'A' ] = new actrie();
		now = now->next[ P[i] - 'A' ];
	}
	
	++now->pcnt;
}

void build()
{
	int front = 0, rear = 1;
	que[0] = root;
	
	while(front < rear)
	{
		actrie *now = que[front], *fnode;
		for(int i = 0; i < 26; i++)
			if(now->next[i])
			{
				fnode = now->flink;
				while(fnode && fnode->next[i] == NULL) fnode = fnode->flink;
				
				if(fnode) now->next[i]->flink = fnode->next[i];
				else now->next[i]->flink = root;
				que[rear++] = now->next[i];
			}
		++front;
	}
}

int match(char * S)
{
	int ret = 0;
	actrie *now = root;
	
	for(int i = 0; S[i]; i++)
	{
		while(now && now->next[ S[i]-'A' ] == NULL) now = now->flink;
		
		if(now)
		{			
			now = now->next[ S[i]-'A' ];
			actrie *temp = now;
			while(temp && temp->pcnt != -1)
			{
				ret += temp->pcnt;
				temp->pcnt = -1;
				temp = temp->flink;
			}			
		}
		else now = root;
	}
	return ret;
}