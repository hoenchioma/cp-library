// Topological Sort and finding Strongly Connected Components (SCC)

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;

#define ff first
#define ss second

const int N = 200;

string word[N];
set<string> dict[N];
map<string, int> ind;
vector<int> graph[N], tgraph[N];

bitset<N> vis;
vector<vector<int>> scc;
int rscc[N];

// finds topological order
void dfs(int u, deque<int>& ans) {
	vis[u] = true;
	for (int v: graph[u]) {
		if (!vis[v]) dfs(v, ans);
	}
	ans.push_front(u);
}

// finds SCC
void dfs2(int u, vector<int>& comp, int ci) {
	vis[u] = true;
	comp.push_back(u);
	rscc[u] = ci;
	for (int v: tgraph[u]) { // traverses transpose graph
		if (!vis[v]) dfs2(v, comp, ci);
	}
}

void dfs3(int c, vector<int>& ans) {
	vis[c] = true;
	for (int u: scc[c]) {
		ans.push_back(u);
		for (int v: graph[u]) {
			if (rscc[v] != c and !vis[rscc[v]]) {
				dfs3(rscc[v], ans);
			}
		}
	}
}

vector<int> solve(int n) {
	deque<int> top;
	vis.reset();
	for (int i = 0; i < n; i++) {
		if (!vis[i]) dfs(i, top);
	}

	vis.reset();
	scc.clear();
	for (int i: top) {
		if (!vis[i]) {
			vector<int> comp;
			dfs2(i, comp, scc.size());
			scc.emplace_back(move(comp));
		}
	}

	vector<int> ans;
	vis.reset();
	for (int i = 0; i < (int)scc.size(); i++) {
		if (scc[i].size() > 1 and !vis[i]) {
			dfs3(i, ans);
		}
	}

	sort(ans.begin(), ans.end(), [&](int x, int y) {
		return word[x] < word[y];
	});

	return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string line, temp;
    while (cin >> n, cin.ignore(), n != 0) {
    	for (int i = 0; i < n; i++) {
    		graph[i].clear();
    		tgraph[i].clear();
    		dict[i].clear();
    	}
    	ind.clear();

    	for (int i = 0; i < n; i++) {
	    	getline(cin, line);
	    	stringstream ss(line);

	    	ss >> word[i];
	    	ind[word[i]] = i;

	    	while (ss >> temp) {
	    		dict[i].insert(temp);
	    	}
    	}
    	for (int i = 0; i < n; i++) {
    		for (const string& j: dict[i]) {
    			graph[i].push_back(ind[j]);
    			tgraph[ind[j]].push_back(i);
    		}
    	}

    	auto ans = solve(n);

    	cout << ans.size() << endl;
    	for (int i = 0; i < (int)ans.size(); i++) {
    		cout << word[ans[i]] << " \n"[i == (int)ans.size()-1];
    	}
    }
    
    return 0;
}
