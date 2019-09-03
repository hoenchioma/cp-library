// Dijkstra 
// (single source shortest path in weighted graph)
// ** weights cannot be negative **
// O(V log (E))

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;

#define ff first
#define ss second

const int N = 600;
const ll INF = INT_MAX-1; // WARNING: be careful of overflow 

vector<pil> adj[N];
ll dis[N];

void dijkstra(int s, int n) {
    fill(dis, dis + n + 1, INF);

    priority_queue<pli, vector<pli>, greater<pli>> pq;
    dis[s] = 0;
    pq.emplace(dis[s], s);

    while (!pq.empty()) {
        int u = pq.top().ss;
        pq.pop();
        for (pil p: adj[u]) {
            int v = p.ff; 
            ll w = p.ss;

            /** relaxation part **/

            ll now = dis[u] + w;
            if (now < dis[v]) {
                dis[v] = now;
                pq.emplace(dis[v], v);
            }
        }
    }
}

int main() {
    int t, cc = 1;
    scanf("%d", &t);

    while (t--) {
        int n, m;
        scanf("%d %d", &n, &m);

        for (int i = 0; i < n; i++) adj[i].clear();

        for (int i = 0; i < m; i++) {
            int u, v;
            ll w;
            scanf("%d %d %lld", &u, &v, &w);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        int s;
        scanf("%d", &s);

        dijkstra(s, n);

        printf("Case %d:\n", cc++);

        for (int i = 0; i < n; i++) {
            if (dis[i] < INF) {
                printf("%lld\n", dis[i]);
            } else {
                printf("Impossible\n");
            }
        }
    }

    return 0;
}
