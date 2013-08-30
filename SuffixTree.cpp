#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;

typedef char U; //Suffix Tree
const int maxS = 1000001, maxSub = 10001, SIZE = maxS;
const U TAIL = 0;

int T, Q, slen;
char text[maxS], sub[maxS];

struct SNode
{
        SNode* suf;
        int s, e;
        int deep;
        
        SNode* get(int ss, int ee, int dd)
        {
                s = ss;
                e = ee;
                deep = dd;
                if(childs.size())
                    childs.clear();
                return this;
        }
    map<U, SNode*> childs;
} snodes[SIZE*2];

int sloc = 0;

pair<SNode*, SNode*> scanv(SNode* w, int s, int e)
{
    int len = 0;
    
    while(true)
        if(s+len >= 3)
            return make_pair(w, w);
    else
    {
        map<U, SNode*>::iterator it = w->childs.find(text[s + len]);
        if(it == w->childs.end())
            return make_pair(w, w);
            
        int t = 0;
        for(int k = it->second->s; k < it->second->e; k++, t++)
            if(text[s + len + t] != text[k])
                break;
                
        if(t == it->second->e - it->second->s)
        {
            w = it->second;
            len += t;
        }    
        else
        {
            SNode* node = snodes[sloc++].get(it->second->s, it->second->s + t, w->deep+t);
            
            node->childs[text[node->e]] = it->second;
            
            it->second->s += t;
            it->second = node;
            
            return make_pair(w, node);
        }
    }
}

SNode* scanw(SNode* n, int s, int e)
{
    while(true)
        if(s >= e)
            return n;
        else
        {
            map<U, SNode*>::iterator it = n->childs.find(text[s]);
            
            if(it->second->e - it->second->s <= e-s)
            {
                s += it->second->e - it->second->s;
                n = it->second;
            }
            else
            {
                SNode* w = snodes[sloc++].get(it->second->s, it->second->s + e -s, n->deep + e - s);
                w->childs[text[w->e]] = it->second;
                
                it->second->s += e - s;
                it->second = w;
                
                w->suf = n->suf;
                return w;
            }
        }
}

SNode* build(int len) //build a suffix tree
{
    SNode* root = snodes[sloc++].get(0, 0, 0);
    root->suf = root;
    SNode* w = root;
    
    for(int i = 0; text[i] != TAIL; i++)
    {
        pair<SNode*, SNode*> v = scanv(w, i + w->deep, len+1);
        
        SNode* tail = snodes[sloc++].get(i + v.second->deep, len + 1, len + 1 - i);
        v.second->childs[text[tail->s]] = tail;
        
        w = scanw(v.first->suf, i + 1 + v.first->suf->deep, i + v.second->deep);
        v.second->suf = w;
    }
    
    return root;
}

bool solve(SNode *now, int st) //if given string appear in main string, return yes
{
    if(now->childs.size()==0) return false;
    map<U, SNode*>::iterator iter = now->childs.begin();
    
    while(iter != now->childs.end())
    {        
        bool res = true;
        int clen = min(slen - st, iter->second->e - iter->second->s);
        
        for(int i = 0; i < clen; i++)
            if(sub[st+i] != text[iter->second->s+i])
            {
                res = false;
                break;
            }        
        
        if(st+clen==slen && res)
            return true;
        if(res)
            return solve(iter->second, st+clen);
            
        ++iter;
    }
    
    return false;
}

int main()
{
    freopen("HEY.txt", "w", stdout);
    scanf("%d\n", &T);
    
    for(int t = 0; t < T; t++)
    {
        sloc = 0;
        scanf("%s\n", &text);
        int len = strlen(text);          
        SNode* sroot = build(len);
                        
        scanf("%d\n", &Q);
        
        while(Q--)
        {
            scanf("%s\n", sub);
            slen = strlen(sub);
            bool res = solve(sroot, 0);
            printf("%s\n", res ? "y" : "n");
        }    
    }
    
    return 0;
}
