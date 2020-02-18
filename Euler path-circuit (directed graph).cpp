// Euler path/circuit in directed graph
// (using Hierholzer algorithm)
// O(E)

// solution to: LOJ 1256

// directed graph: circuit (or edge disjoint directed cycles) exists iff each node 
//  satisfies in_degree = out_degree and the graph is strongly connected
// directed graph: path exists iff at most one vertex has in_degree - out_degree = 1
//  and at most one vertex has out_degree - in_degree = 1 and all other vertices have
//  in_degree = out_degree, and graph is weakly connected

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<char, char> pcc;

#define ff first
#define ss second

const int N = 2000;

map<char, vector<char>> adj;
map<char, vector<char>> tadj;
map<pcc, vector<int>> ind;
string str[N];

bitset<30> vis;

void dfs(char u) {
  vis[u - 'a'] = true;
  for (char v: adj[u]) {
    if (!vis[v - 'a']) dfs(v);
  }
  for (char v: tadj[u]) {
    if (!vis[v - 'a']) dfs(v);
  }
}

pair<pcc, bool> checkEuler(set<char>& let) {
  pcc ans = {'\0', '\0'};
  for (char i: let) {
    if (adj[i].size() != tadj[i].size()) {
      if ((int)adj[i].size() - (int)tadj[i].size() == 1) {
        if (ans.ff == '\0') ans.ff = i;
        else return {ans, false};
      }
      else if ((int)adj[i].size() - (int)tadj[i].size() == -1) {
        if (ans.ss == '\0') ans.ss = i;
        else return {ans, false};
      }
      else return {ans, false};
    }
  }
  if (ans.ff == '\0' and ans.ss == '\0') {
    ans.ff = *let.begin();
    ans.ss = *let.begin();
  }
  else if (ans.ff == '\0' or ans.ss == '\0') return {ans, false};

  vis.reset();
  int comp = 0;
  for (char i: let) {
    if (!vis[i - 'a']) {
      dfs(i);
      comp++;
    }
    if (comp > 1) return {ans, false};
  }

  return {ans, true};
}

// euler path in directed graph
deque<char> euler(set<char>& let) {
  auto res = checkEuler(let);

  if (!res.ss) return {};

  char start = res.ff.ff;

  stack<char> cur;
  deque<char> path;

  cur.push(start);

  while (!cur.empty()) {
    char top = cur.top();
    if (!adj[top].empty()) {
      cur.push(adj[top].back());
      adj[top].pop_back();
    } else {
      path.push_front(top);
      cur.pop();
    }
  }

  return path;
} 

// finding the order of an array of strings where
// last char of i = first char of j, for every adjacent pair (i, j)
int main() {
  int t, cc = 1;
  scanf("%d", &t);

  char tstr[50];

  while (t--) {
    int n;
    scanf("%d", &n);

    adj.clear(), tadj.clear(), ind.clear();
    set<char> let;
    for (int i = 0; i < n; i++) {
      scanf("%s", tstr);
      str[i] = move(string(tstr));
      char start = str[i].front(), end = str[i].back();
      adj[start].push_back(end);
      tadj[end].push_back(start);
      ind[{start, end}].push_back(i);
      let.insert(start), let.insert(end);
    }

    auto res = euler(let);

    if (res.empty()) {
      printf("Case %d: No\n", cc++);
    } else {
      printf("Case %d: Yes\n", cc++);

      vector<int> ans;
      for (int i = 1; i < (int)res.size(); i++) {
        ans.push_back(ind[{res[i-1], res[i]}].back());
        ind[{res[i-1], res[i]}].pop_back();
      }
      for (int i = 0; i < (int)ans.size(); i++) {
        printf("%s%c", str[ans[i]].c_str(), " \n"[i == (int)ans.size()-1]);
      }
    }
  }
  
  return 0;
}