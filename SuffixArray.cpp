class SuffixArray {
    string str;
    vector<vector <int>> rank;
    vector <int> finalRank;
    int logLevel;

    void rankInitialization() {
        map <char, int> rankMap;

        for (int i = 0; i < str.size(); ++i) {
            rankMap[str[i]] = 1;
        }

        auto iter = rankMap.begin();
        int cnt = 0;
        while (iter != rankMap.end()) {
            iter->second = cnt++;
            ++iter;
        }

        for (int i = 0; i < str.size(); ++i) {
            rank[0][i] = rankMap[str[i]];
        }
    }

    inline int cmpDir(int diff) {
        return diff == 0 ? 0 : diff/abs(diff);
    }

    inline int cmp(int i, int j, int l) {
        // sorting => s[i][l]+s[i+(1<<l)][l] vs s[j][l] + s[j+(l<<l)][l]
        if (rank[l][i] != rank[l][j]) {
            return cmpDir(rank[l][i] - rank[l][j]);
        }

        int ni = i + (1<<l);
        int nj = j + (1<<l);

        if (ni < str.size() && nj >= str.size()) {
            return 1;
        } else if (ni >= str.size() && nj < str.size()) {
            return -1;
        } else if (ni >= str.size() && nj >= str.size()) {
            return 0;
        }

        return cmpDir(rank[l][ni] - rank[l][nj]);
    }

    void sortArr(vector<int>& arr, int s, int e, int l) {
        if (s >= e) {
            return ;
        }

        int pivot = (s+e) / 2;
        int cnt = 0;
        int flag = 0;

        swap(arr[s], arr[pivot]);

        for (int i = s+1; i <= e; ++i) {
            if (cmp(arr[s], arr[i], l-1) == 1) {
                swap(arr[s+(++cnt)], arr[i]);
            } else if (cmp(arr[s], arr[i], l-1) == 0) {
                // evenly distributed
                if (flag) {
                    swap(arr[s+(++cnt)], arr[i]);
                }
                flag ^= 1;
            }
        }

        swap(arr[s], arr[s+cnt]);
        sortArr(arr, s, s+cnt-1, l);
        sortArr(arr, s+cnt+1, e, l);
    }

public:
    SuffixArray(string& s) {
        str = s;

        logLevel = 1;

        while ((1<<logLevel) < str.size()) {
            ++logLevel;
        }

        rank = move(vector<vector<int>>(logLevel+1, vector<int>(str.size())));
        finalRank = move(vector<int>(str.size()));
    }

    void buildSuffixArray() {
        rankInitialization();

        vector <int> arr(str.size());
        for (int i = 0; i < str.size(); ++i) {
            arr[i] = i;
        }

        // level sorting
        for (int l = 1; l <= logLevel; ++l) {
            sortArr(arr, 0, arr.size()-1, l);

            int cnt = 1;
            rank[l][arr[0]] = 0;

            for (int i = 1; i < arr.size(); ++i) {
                if (cmp(arr[i], arr[i-1], l-1) != 0) {
                    rank[l][arr[i]] = cnt++;
                } else {
                    rank[l][arr[i]] = rank[l][arr[i-1]];
                }
            }
        }

        for (int i = 0; i < str.size(); ++i) {
            finalRank[rank[logLevel][i]] = i;
        }
    }

    int getRankIdx(int rank) {
        if (rank < str.size()) {
            return finalRank[rank];
        }

        return -1;
    }
};