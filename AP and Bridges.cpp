// Articulation Points and Bridges

// AP: points if removed increases component no. in graph
// bridge: edges if removed increases component no. in graph

#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

#define ff first
#define ss second

const int N = 10009;

vector<int> graph[N];
int disc[N], low[N];
bool ap[N];

// marks APs and bridges and returns the total number of APs
int dfs(int u, int p, vector<pii>& bridge) {
	static int time = 0;
	low[u] = disc[u] = time++;

	int ans = 0, child = 0;
	for (int v: graph[u]) {
		if (disc[v] == -1) {
			child++;
			ans += dfs(v, u, bridge);
			low[u] = min(low[u], low[v]);

			// checking AP
			if (p == -1 and child > 1) ap[u] = true;
			if (p != -1 and disc[u] <= low[v]) ap[u] = true;

			// checking bridge
			if (disc[u] < low[v]) {
				if (u < v) bridge.push_back({u, v});
				else bridge.push_back({v, u});
			}
		} else if (v != p) {
			low[u] = min(low[u], disc[v]);
		}
	}
	return ans;
}

// returns the AP count and list of bridges
pair<int, vector<pii>> findAP(int n) {
	fill(disc, disc+n+1, -1);
	int ans = 0;
	vector<pii> bridge;
	for (int i = 1; i <= n; i++) {
		if (disc[i] == -1) ans += dfs(i, -1, bridge);
	}
	sort(bridge.begin(), bridge.end());
	return {ans, bridge};
}

int main() {
	int t, cc = 1;
	cin >> t;

	while (t--) {
		int n, m;
		scanf("%d %d", &n, &m);

		for (int i = 0; i < m; i++) {
			int u, v;
			scanf("%d %d", &u, &v);
			graph[u].push_back(v);
			graph[v].push_back(u);
		}

		printf("Case %d: %d\n", cc++, findAP(n).ff);

		for (int i = 1; i <= n; i++) graph[i].clear();
	}
}
