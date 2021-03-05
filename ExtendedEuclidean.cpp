struct GCDInfo {
    long long x;
    long long y;
    long long g;
    GCDInfo(long long px, long long py, long long pg) : x(px), y(py), g(pg) {
    }
};

GCDInfo gcd(long long a, long long b) {
    if (b == 0) {
        return GCDInfo(1, 0, a);
    }

    // ax+by = g
    // bx'+(a-a/b*b)y' = g
    GCDInfo v = gcd(b, a%b);
    return GCDInfo(v.y%(b/v.g), (v.x-(a/b)*v.y)%(a/v.g), v.g);
}

// Get a * x mod p = 1
long long findInv(long long a, long long p) {
    return gcd(a, p).x;
}