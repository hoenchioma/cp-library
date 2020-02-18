// Euler path/circuit in undirected graph
// (using Hierholzer algorithm)
// O(E)

// solution to: https://www.hackerrank.com/contests/cse-2212-lab-exam-1-20190903/challenges/euler-euler

// undirected graph: circuit (or edge disjoint cycles) exists iff all nodes are of even degree
// undirected graph: path exists iff number of odd degree nodes is zero or two

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

#define ff first
#define ss second

const int N = 100009;
const ll INF = 1e8;

struct Node { 
  int id; 
  list<Node>::iterator rev; // iterator (pointer) of reverse edge node

  // for auto casting to and from int
  Node(int id): id(id) {}
  operator int() const { return id; }
};

list<Node> adj[N];
bitset<N> vis;

pair<pii, bool> checkEuler(set<int>& node) {
  pii ans = {-1, -1};
  for (int i: node) {
    if (adj[i].size() & 1) {
      if (ans.ff == -1) ans.ff = i;
      else if (ans.ss == -1) ans.ss = i;
      else return {ans, false};
    }
  }
  if (ans.ff == -1 and ans.ss == -1) return {ans, true};
  else if (ans.ff == -1 or ans.ss == -1) return {ans, false};
  return {ans, true};
}

void dfs(int u) {
  vis[u] = true;
  for (int v: adj[u]) {
    if (!vis[v]) dfs(v);
  }
}

deque<int> euler(set<int>& node) {
  auto res = checkEuler(node);
  if (!res.ss) return {};

  int count = 0;
  vis.reset();
  for (int i: node) {
    if (!vis[i]) {
      count++;
      if (count > 1) return {};
      dfs(i);
    }
  }

  int start;
  if (res.ff.ff == -1) start = *node.begin(); // choose arbitrary vertex (first) if circuit
  else start = res.ff.ff;

  stack<int> cur;
  deque<int> path;

  cur.push(start);

  while (!cur.empty()) {
    int top = cur.top();
    if (!adj[top].empty()) {
      int u = top;
      Node v = adj[top].front();
      cur.push(v);

      // delete edge u--v
      adj[v].erase(v.rev); // this part is not needed in directed graph
      adj[u].pop_front();
    } else {
      path.push_front(top);
      cur.pop();
    }
  }

  return path;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  set<int> node;
  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;

    adj[u].push_front(v);
    adj[v].push_front(u);
    // store the reverse iterator (pointer) in rev
    adj[u].front().rev = adj[v].begin();
    adj[v].front().rev = adj[u].begin();
    node.insert(u), node.insert(v);
  }
  
  auto res = euler(node);

  if (res.empty()) {
    cout << "None" << endl;
  } else {
    if (res.front() == res.back()) cout << "Euler Circuit" << endl;
    else cout << "Euler Path" << endl;

    for (int i = 0; i < (int) res.size(); i++) {
      cout << res[i] << " \n"[i == (int) res.size() - 1];
    }
  }

  return 0;
}