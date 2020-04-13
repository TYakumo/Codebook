const int MOD = 1000000000 + 7;
const int MAXN = 2;

struct Mat {
    vector< vector <long long> > val;

    Mat() {
        val = move(vector< vector <long long> >(MAXN, vector<long long>(MAXN)));
    }

    inline Mat iden() {
        Mat ret;
        for (int i = 0; i < MAXN; ++i) {
            ret.val[i][i] = 1;
        }
        return ret;
    }

    Mat matpow(int n) {
        if (n == 0) {
            return iden();
        }

        Mat half = matpow(n/2);

        return n%2 == 0 ? half*half : half*half*(*this);
    }

    Mat operator*(const Mat& m) {
        Mat ret;

        for (int i = 0; i < MAXN; ++i) {
            for (int j = 0; j < MAXN; ++j) {
                for (int k = 0; k < MAXN; ++k) {
                    ret.val[i][j] += val[i][k] * m.val[k][j];
                    ret.val[i][j] %= MOD;
                }
            }
        }

        return ret;
    }
};