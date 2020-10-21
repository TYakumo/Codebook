
using VI = vector <int>;
using VVI = vector <VI>;

template <typename C>
struct Edge
{
    int to;
    int cp;
    C cap;

    Edge() {}
    Edge(int pt, C pcap, int pcp) : to(pt), cap(pcap), cp(pcp) { }
};

template <typename C>
class FlowGraph {
using VE = vector <Edge<C>>;
using VVE = vector <VE>;
const C INF = 10000000;
    VVE adja;
    int src;
    int sink;
    int V;
    VI dist;
    VI num;
public:
    FlowGraph (int pv) : V(pv) {
        adja = VVE(pv);
        dist = VI(pv);
        num = VI(pv+1); // can be num[V]
    }

    void addEdge(int f, int t, C c) {
        adja[f].push_back( Edge(t, c, adja[t].size()) );
        adja[t].push_back( Edge(f, 0, adja[f].size()-1) );
    }

    C aug(int now, C leftCap) {
        if(now == sink) {
            return leftCap;
        }

        C remainCap = leftCap;
        int minDist = V;

        for(int i = 0; i < adja[now].size(); i++) {
            int nextv = adja[now][i].to;

            if(adja[now][i].cap > 0 && dist[now] == dist[nextv]+1) {
                C flow = aug(nextv, min(remainCap, adja[now][i].cap));
                adja[now][i].cap -= flow;
                remainCap -= flow;
                adja[nextv][ adja[now][i].cp ].cap += flow;

                if (dist[src] == V || remainCap == 0) {
                    return leftCap-remainCap;
                }
            }
        }

        if(dist[src] == V) {
            return leftCap-remainCap;
        }

        if(remainCap == leftCap) {
            for(int i = 0; i < adja[now].size(); i++) {
                if(adja[now][i].cap) {
                    minDist = min(minDist, dist[ adja[now][i].to ]+1);
                }
            }

            if(--num[ dist[now] ]) {
                ++num[ dist[now] = minDist ];
            }
            else {
                dist[src] = V;
            }
        }
        return leftCap-remainCap;
    }

    C flow(int psrc, int psink) {
        C ret = 0;
        src = psrc;
        sink = psink;

        fill(dist.begin(), dist.end(), 0);
        fill(num.begin(), num.end(), 0);
        num[src] = V;

        while (dist[src] < V) {
            ret += aug(src, INF);
        }

        return ret;
    }
};
