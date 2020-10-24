template <typename T>
struct Edge {
    int to;
    T w;

    Edge() {}
    Edge(int pt, T pw) : to(pt), w(pw) { }
};

template <typename T>
class SPFA {
    using VE = vector<Edge<T>>;
    using VVE = vector<VE>;
    using VI = vector <int>;
    using VT = vector <T>;
    // const T INF = 1000000000;

    int V;
    VI prev;
    VVE adja;
    VT dist;

public:
    SPFA(int PV) {
        V = PV;
        adja = VVE(V);
        prev = VI(V, -1);
        dist = VT(V, INF);
    }

    bool sssp(int src) {
        deque <int> que;
        VI inQue(V);
        VI prevTime(V);

        dist[src] = 0;
        inQue[src] = 1;
        que.push_back(src);

        while (!que.empty()) {
            int now = que.front();
            que.pop_front();

            inQue[now] = 0;

            for (int i = 0; i < adja[now].size(); ++i) {
                int nextv = adja[now][i].to;
                T newdist = dist[now] + adja[now][i].w;

                if (newdist < dist[nextv]) {
                    dist[nextv] = newdist;
                    prev[nextv] = now;
                    prevTime[nextv] = prevTime[now] + 1;

                    if (prevTime[nextv] == V) {
                        return true; // negative cycle
                    }

                    if (inQue[nextv] == 0) {

                        if (que.empty() || dist[nextv] >= dist[que.front()]) {
                            que.push_back(nextv);
                        } else {
                            que.push_front(nextv);
                        }

                        inQue[nextv] = 1;
                    }
                }
            }
        }

        return false;
    }

    T getBest(int v) {
        return dist[v];
    }

    void addEdge(int f, int t, T w) {
        adja[f].emplace_back(Edge(t, w));
    }

    vector <int> findPath(int src, int dest) {
        vector <int> ret;
        int now = dest;

        while (now != -1) {
            ret.push_back(now);
            now = prev[now];
        }

        if (!ret.empty() && ret.back() != src) { // src can't connect to dest
            ret.clear();
        } else {
            reverse(ret.begin(), ret.end());
        }

        return ret;
    }
};