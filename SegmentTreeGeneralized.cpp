template<class T>
class SetOp {
public:
    inline T op(T a, T b) {
        return a || b;
    }

    inline T retOp(T a, T b) {
        return a + b;
    }

    inline T childOp(T a, T b) {
        return a + b;
    }

    inline T parentToChildOp(T a, T b) {
        return a ? a : b;
    }

    inline T sumOp(T val, T sx, T ex) {
        return val * (ex-sx);
    }
};

template<class T>
class MaxOp {
public:
    inline T op(T a, T b) {
        return max(a, b);
    }

    inline T retOp(T a, T b) {
        return max(a, b);
    }

    inline T childOp(T a, T b) {
        return max(a, b);
    }

    inline T parentToChildOp(T a, T b) {
        return max(a, b);
    }

    inline T sumOp(T val, T sx, T ex) {
        return val;
    }
};

template<class T, class C, class O>
class SegmentTree {
    const T INIT_VAL = 0;
    T val;
    T sum;
    O op;
    int sx;
    int ex;
    vector <SegmentTree *> children;

    inline void recalculateSum() {
        this->sum = op.sumOp(this->val, sx, ex);

        T childSum = 0;
        for (int i = 0; i < children.size(); ++i) {
            childSum = op.childOp(childSum, children[i]->sum);
        }

        this->sum = op.parentToChildOp(this->sum, childSum);
    }

    inline void propagateVal() {
        if (children.size() != 0) {

            for (int i = 0; i < children.size(); ++i) {
                children[i]->val = op.op(children[i]->val, this->val);
                children[i]->recalculateSum();
            }

            this->val = 0;
            recalculateSum();
        }
    }

    inline void checkAndCreateChildren() {
        if (children.size() == 0) {
            C mid =  (sx + ex) / 2;

            children.emplace_back(new SegmentTree(sx, mid));
            children.emplace_back(new SegmentTree(mid, ex));
            propagateVal();
        }
    }

public:

    SegmentTree (C spaceSize) {
        sum = val = INIT_VAL;
        sx = ex = 0;

        ex = 1;
        while (ex < spaceSize) {
            ex *= 2;
        }
    }

    SegmentTree (C psx, C pex) : sx(psx), ex(pex) {
        sum = val = INIT_VAL;
    }

    void updateSegment(C x1, C x2, T v) {
        if (x1 >= x2) {
            return ;
        }

        if (x1 == sx && x2 == ex) {
            val = op.op(val, v);
            recalculateSum();
            return ;
        }

        C mid =  (sx + ex) / 2;
        checkAndCreateChildren();
        propagateVal();

        if (x1 < mid) {
            children[0]->updateSegment(x1, min(x2, mid), v);
        }

        if (ex > mid) {
            children[1]->updateSegment(max(x1, mid), x2, v);
        }

        recalculateSum();
    }

    T query(C x1, C x2) {
        if (x1 >= x2) {
            return INIT_VAL;
        }

        if (x1 == sx && x2 == ex) {
            return this->sum;
        }

        T ret = 0;
        C mid =  (sx + ex) / 2;
        checkAndCreateChildren();
        propagateVal();

        if (x1 < mid) {
            ret = op.retOp(ret, children[0]->query(x1, min(x2, mid)));
        }

        if (x2 > mid) {
            ret = op.retOp(ret, children[1]->query(max(x1, mid), x2));
        }

        recalculateSum();

        return ret;
    }
};