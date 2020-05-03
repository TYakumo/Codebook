#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
using namespace std;

using VI = vector <int>;
using VVI = vector <VI>;

struct SegmentTree {
    const int INVALID_VAL = -1;
    int val;
    int from;
    int to;
    SegmentTree *left;
    SegmentTree *right;

    SegmentTree (int treeSize) {
        from = 0;
        to = 1;
        val = INVALID_VAL;

        while ((to-from) < treeSize) {
            to *= 2;
        }

        left = right = nullptr;
    }

    SegmentTree (int pf, int pt) : from(pf), to(pt) {
        val = INVALID_VAL;
        left = right = nullptr;
    }

    int updateSegment(int f, int t, int val) {
        if (f >= t) {
            return INVALID_VAL;
        }

        if (f == from && t == to) {
            this->val = val;
            return this->val;
        }

        int mid = (from + to) / 2;
        if (left == nullptr) {
            left = new SegmentTree(from, mid);
            right = new SegmentTree(mid, to);
        }

        if (t > mid) {
            right->updateSegment(max(f, mid), t, val);
        }

        if (f < mid) {
            left->updateSegment(f, min(t, mid), val);
        }

        this->val = max(left->val, right->val);
        return this->val;
    }

    int findMax(int f, int t) {
        if (f >= t) {
            return INVALID_VAL;
        }

        if (f == from && t == to) {
            return this->val;
        }

        int mid = (from + to) / 2;
        int maxVal = INVALID_VAL;

        if (left == nullptr) {
            left = new SegmentTree(from, mid);
            right = new SegmentTree(mid, to);
        }

        if (t > mid) {
            maxVal = max(maxVal, right->findMax(max(f, mid), t));
        }

        if (f < mid) {
            maxVal = max(maxVal, left->findMax(f, min(t, mid)));
        }

        return maxVal;
    }
};