using VI = vector <int>;
using VVI = vector <VI>;

class SCCGraph {
    VI dfn;
    VI low;
    VI run;
    VI groupNum;
    VI inStack;
    VI stack;
    VVI adja;
    int round;
    int timeStamp;
    int curGroup;

    void __tarjan(int now) {
        dfn[now] = low[now] = ++timeStamp;
        run[now] = round;
        inStack[now] = 1;
        stack.push_back(now);

        for(int i = 0; i < adja[now].size(); i++) {
            int nextn = adja[now][i];
            if(run[nextn] == 0) { // white
                __tarjan(nextn);
                low[now] = min(low[now], low[nextn]);
            } else if(inStack[nextn]) { //gray
                low[now] = min(low[now], dfn[nextn]);
            }
        }

        if (low[now] == dfn[now]) {
            int top = 0;
            do {
                groupNum[top] = curGroup;
                top = stack.back();
                stack.pop_back();
                inStack[top] = 0;
            } while (low[top] != dfn[top]);
            ++curGroup;
        }
    }

public:
    SCCGraph (int V) {
        dfn = move(VI(V));
        low = move(VI(V));
        run = move(VI(V));
        inStack = move(VI(V));
        groupNum = move(VI(V, -1));
        adja = move(VVI(V));
        curGroup = timeStamp = round = 0;
    }

    void computeSCC() {
        int V = dfn.size();
        for (int i = 0; i < V; i++) {
            if (run[i] != round) {
                __tarjan(i);
            }
            ++round;
        }
    }

    void addEdge(int f, int t) {
        adja[f].push_back(t);
    }

    int getGroupNum(int v) {
        return groupNum[v];
    }
};
