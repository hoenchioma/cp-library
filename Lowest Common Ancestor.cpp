// Lowest Common Ancestor (using binary lifting)
// O(log(height of tree))

// solution to: SPOJ LCA

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, cc = 1; cin >> t;
    while (t--) {
        cout << "Case " << cc++ << ":" << endl;

        int n;
        cin >> n;
        lca::adj.assign(n+1, vector<int>{});
        lca::n = n+1;
        for (int i = 1; i <= n; i++) {
            int m; cin >> m;
            for (int j = 0; j < m; j++) {
                int x; cin >> x;
                lca::adj[i].push_back(x);
            }
        }

        lca::preprocess(1);

        int q; cin >> q;
        for (int i = 0; i < q; i++) {
            int x, y; cin >> x >> y;
            cout << lca::lca(x, y) << endl;
        }
    }
    return 0;
}