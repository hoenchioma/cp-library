// Biconnected Components
// (maximal bi-connected subgraph)
// (bi-connected: any two vertices have at least two distinct paths between them, contains no articulation points)
// solution to: https://www.hackerrank.com/contests/cse-2212-lab-exam-1-20190903/challenges/all-the-components/problem

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

#define ff first
#define ss second

const int N = 1e5 + 9;
const ll INF = 1e8;

vector<int> adj[N];
int low[N], disc[N];

// makes a vector of biconnected components (with nodes)
void dfs(int u, int p, vector<set<int>>& bcc, stack<int>& st) {
    static int time = 0;
    low[u] = disc[u] = time++;
    st.push(u);
    
    for (int v: adj[u]) {
        if (disc[v] == -1) {
            dfs(v, u, bcc, st);
            low[u] = min(low[u], low[v]);

            if (disc[u] <= low[v]) {
                set<int> comp;
                while (disc[st.top()] >= disc[v]) {
                    comp.insert(st.top());
                    st.pop();
                }
                comp.insert(u); // insert the AP separately
                bcc.emplace_back(move(comp));
            }
        }
        else if (v != p) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<set<pii>> solve(int n) {
    fill(disc, disc + n, -1);

    vector<set<int>> bcc;
    stack<int> st;
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            dfs(i, -1, bcc, st);
        }
    }
    
    // makes bc of edges from bc of nodes

    vector<set<pii>> ans;
    for (auto& comp: bcc) {
        set<pii> acomp;
        for (int u: comp) {
            for (int v: adj[u]) {
                if (comp.find(v) != comp.end()) {
                    if (u < v) acomp.insert({u, v});
                    else acomp.insert({v, u});
                }
            }
        }
        ans.emplace_back(move(acomp));
    }
    
    sort(ans.begin(), ans.end());

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto res = solve(n);

    for (int i = 0; i < (int) res.size(); i++) {
        for (pii p: res[i]) {
            cout << p.ff << " " << p.ss << endl;
        }
        if (i < (int) res.size() - 1) cout << "---" << endl;
    }

    return 0;
}