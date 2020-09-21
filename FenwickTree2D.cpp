template<class T>
class FenwickTree2D {
    vector< vector <T> > sum;

    void __addVal(int idxX, int idxY, T val) {
        while (idxY < sum[idxX].size()) {
            sum[idxX][idxY] += val;
            idxY += (idxY & (-idxY));
        }
    }

    T __getVal(int idxX, int idxY) {
        T ret = 0;

        while (idxY) {
            ret += sum[idxX][idxY];
            idxY -= (idxY & (-idxY));
        }

        return ret;
    }

public:
    FenwickTree2D (int treeSizeX, int treeSizeY) {
        sum = move(vector<vector<T>>(treeSizeX+1, vector<T>(treeSizeY+1)));
    }

    void addVal(int idxX, int idxY, T val) {
        while (idxX < sum.size()) {
            __addVal(idxX, idxY, val);
            idxX += (idxX & (-idxX));
        }
    }

    T getVal(int idxX, int idxY) {
        if (idxX <= 0 || idxY <= 0) {
            return 0;
        }

        T ret = 0;

        while (idxX) {
            ret += __getVal(idxX, idxY);
            idxX -= (idxX & (-idxX));
        }

        return ret;
    }

    T queryRange(int sx, int sy, int ex, int ey) {
        T ret = getVal(ex, ey);

        if (sx - 1 >= 0) {
            ret -= getVal(sx-1, ey);
        }

        if (sy - 1 >= 0) {
            ret -= getVal(ex, sy-1);
        }

        if (sx - 1 >= 0 && sy - 1 >= 0) {
            ret += getVal(sx-1, sy-1);
        }

        return ret;
    }
};