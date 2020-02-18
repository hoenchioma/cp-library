// Dijkstra 
// (single source shortest path in weighted graph)
// ** weights cannot be negative **
// O(V log (E))

typedef long long ll;
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
    ll du = pq.top().ff;
    pq.pop();

    if (du != dis[u]) continue; // check if it is an old entry

    for (pil p: adj[u]) {
      int v = p.ff; ll w = p.ss;

      /** relaxation part **/

      ll now = dis[u] + w;
      if (now < dis[v]) {
        dis[v] = now;
        pq.emplace(dis[v], v);
      }
    }
  }
}
