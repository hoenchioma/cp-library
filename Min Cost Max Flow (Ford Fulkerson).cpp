// Min Cost Max Flow 
// Uses Ford Fulkerson algo along with Bellman Ford SPFA
// O(V^2 * E^2)

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

using ll = long long;

const int N = 200;
const ll INF = INT_MAX-1;

vector<int> adj[N];
ll cost[N][N], cap[N][N];

void bFord(int s, int n, vector<ll>& d, vector<int>& par) {
  d.assign(n, INF);
  d[s] = 0;
  par.assign(n, -1);
  queue<int> qq;
  qq.push(s);
  vector<bool> inQ(n, false);

  while (!qq.empty()) {
    int u = qq.front();
    qq.pop();
    inQ[u] = false;
    for (int v: adj[u]) {
      if (cap[u][v] && d[u] + cost[u][v] < d[v]) {
        d[v] = d[u] + cost[u][v];
        par[v] = u;
        if (!inQ[v]) {
          inQ[v] = true;
          qq.push(v);
        }
      }
    }
  }
}

pair<ll, ll> maxFlow(int s, int t, int n) {
  ll flow = 0, cost = 0;
  vector<ll> d;
  vector<int> p;

  while (true) {
    bFord(s, n, d, p);
    if (d[t] == INF) break;

    ll tflow = INF;
    for (int cur = t; cur != s; cur = p[cur]) {
      tflow = min(tflow, cap[p[cur]][cur]);
    }

    flow += tflow;
    cost += tflow * d[t];
    for (int cur = t; cur != s; cur = p[cur]) {
      cap[p[cur]][cur] -= tflow;
      cap[cur][p[cur]] += tflow;
    }
  }

  return {flow, cost};
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

  int t, cc = 1;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    for (int i = 0; i < 2*n+2; i++) adj[i].clear();

    vector<ll> a(2*n);

    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    for (int i = n; i < 2*n; i++) {
      cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
      for (int j = n; j < 2*n; j++) {
        adj[i].push_back(j);
        adj[j].push_back(i);
        cap[i][j] = 1;
        cap[j][i] = 0;
        ll w;
        if (a[i] > a[j]) w = 2;
        else if (a[i] == a[j]) w = 1;
        else w = 0;
        cost[i][j] = -w;
        cost[j][i] = w;
      }
    }

    int s = 2*n, t = 2*n+1;

    for (int i = 0; i < n; i++) {
      adj[s].push_back(i);
      adj[i].push_back(s);
      cap[s][i] = 1;
      cap[i][s] = 0;
      cost[s][i] = cost[i][s] = 0;
    }

    for (int i = n; i < 2*n; i++) {
      adj[i].push_back(t);
      adj[t].push_back(i);
      cap[i][t] = 1;
      cap[t][i] = 0;
      cost[t][i] = cost[i][t] = 0;
    }

    // for (int i = 0; i < 2*n+2; i++) {
    //   cout << i << ": ";
    //   for (int j: adj[i]) cout << j << " ";
    //   cout << endl;
    // }

    // auto res = maxFlow(s, t, 2*n+2);
    // cout << res.first << " " << res.second << endl;
    ll ans = -maxFlow(s, t, 2*n+2).second;
    cout << "Case " << cc++ << ": " << ans << endl;
  }

  return 0;
}