
using VI = vector <int> ;
using VVI = vector <VI> ;

class FenwickTree {
    VI sum;
public:
    FenwickTree (int treeSize) {
        sum = move(VI(treeSize+1));
    }

    void addVal(int idx, int val) {
        while (idx < sum.size()) {
            sum[idx] += val;
            idx += (idx & (-idx));
        }
    }

    int getVal(int idx) {
        if (idx <= 0) {
            return 0;
        }

        int ret = 0;

        while (idx) {
            ret += sum[idx];
            idx -= (idx & (-idx));
        }

        return ret;
    }

    int queryRange(int a, int b) {
        return getVal(b) - getVal(a-1);
    }
};