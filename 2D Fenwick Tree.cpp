// 2D Fenwick Tree (BIT)
// (finds the prefix sum of a block of a matrix)
// O(log(mn))

#include <bits/stdc++.h>
using namespace std;

// one based 2D Fenwick Tree
template <typename T, size_t M, size_t N>
struct Fenwick2D {
    T bit[M+1][N+1];
    int m = M, n = N;

    void init(int m, int n) {
        this->m = m, this->n = n;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                bit[i][j] = 0;
            }
        }
    }

    T sum(int x, int y) {
        T res = 0;
        for (int i = x; i > 0; i -= (i & -i)) {
            for (int j = y; j > 0; j -= (j & -j)) {
                res += bit[i][j];
            }
        }
        return res;
    }

    void update(int x, int y, T del) {
        for (int i = x; i <= m; i += (i & -i)) {
            for (int j = y; j <= n; j += (j & -j)) {
                bit[i][j] += del;
            }
        }
    }

    inline T sum(int i1, int j1, int i2, int j2) {
        return sum(i2, j2) - sum(i2, j1-1) - sum(i1-1, j2) + sum(i1-1, j1-1);
    }

    inline T get(int i, int j) {
        return sum(i, j, i, j);
    }

    inline void set(int i, int j, T val) {
        update(i, j, val - get(i, j));
    }
};

Fenwick2D<int, N, N> fw;