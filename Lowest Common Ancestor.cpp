// Lowest Common Ancestor (using binary lifting)
// O(log(height of tree))

#include <bits/stdc++.h>
using namespace std;

namespace lca {
    int n, l, timer;
    vector<vector<int>> adj;

    vector<int> tin, tout;
    vector<int> depth;
    vector<vector<int>> up;

    void dfs(int v, int p, int d = 0) {
        tin[v] = ++timer;
        up[v][0] = p;
        depth[v] = d;
        for (int i = 1; i <= l; i++) {
            up[v][i] = up[up[v][i-1]][i-1];
        }
        for (int u : adj[v]) {
            if (u != p) dfs(u, v, d+1);
        }
        tout[v] = ++timer;
    }

    inline bool is_ancestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    int lca(int u, int v) {
        if (is_ancestor(u, v)) return u;
        if (is_ancestor(v, u)) return v;
        for (int i = l; i >= 0; i--) {
            if (!is_ancestor(up[u][i], v)) u = up[u][i];
        }
        return up[u][0];
    }

    void preprocess(int root) {
        tin.resize(n);
        tout.resize(n);
        depth.resize(n);
        l = ceil(log2(n));
        up.assign(n, vector<int>(l + 1));
        timer = 0;
        dfs(root, root);
    }
}