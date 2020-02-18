// Suffix Automata

#include <bits/stdc++.h>
using namespace std;

namespace sa {
  // *** nodes on the path from last to init state (0) contains all terminal states (suffixes)

  struct state {
    int len, link, fpos;
    map<char, int> next;
    // minlen(v) = len(link(v)) + 1
  };

  const int MAXLEN = 100000;
  state st[MAXLEN * 2];
  int sz, last;

  void init() {
    st[0].len = 0;
    st[0].link = -1;
    st[0].fpos = -1;
    sz = 1;
    last = 0;
  }

  void extend(char c) {
    int cur = sz++;
    st[cur].len = st[last].len + 1;
    st[cur].fpos = st[cur].len - 1;
    int p = last;
    while (p != -1 && !st[p].next.count(c)) {
      st[p].next[c] = cur;
      p = st[p].link;
    }
    if (p == -1) {
      st[cur].link = 0;
    } else {
      int q = st[p].next[c];
      if (st[p].len + 1 == st[q].len) {
        st[cur].link = q;
      } else {
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        st[clone].fpos = st[q].fpos;
        while (p != -1 && st[p].next[c] == q) {
          st[p].next[c] = clone;
          p = st[p].link;
        }
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
}