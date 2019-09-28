// Segment Tree (iterative)
// O(log(n))

// source: https://codeforces.com/blog/entry/18051

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5; // limit for array size

// range sum and point update
namespace seg {
  int n; // array size
  int t[2 * N];

  void _build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
  }

  void init(int a[], int n) {
    seg::n = n;
    for (int i = 0; i < n; i++) {
      t[n + i] = a[i];
    }
    _build();
  }

  void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1) t[p>>1] = t[p] + t[p^1];
  }

  int query(int l, int r) {  // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }
}

// range increment and range max
// (order of updates not important)
namespace seg1 {
  int n; // array size
  int t[2 * N];

  int h = sizeof(int) * 8 - __builtin_clz(n); // height of tree
  int d[N];

  void _apply(int p, int value) {
    t[p] += value;
    if (p < n) d[p] += value;
  }

  void _build(int p) {
    while (p > 1) p >>= 1, t[p] = max(t[p<<1], t[p<<1|1]) + d[p];
  }

  void _push(int p) {
    for (int s = h; s > 0; --s) {
      int i = p >> s;
      if (d[i] != 0) {
        _apply(i<<1, d[i]);
        _apply(i<<1|1, d[i]);
        d[i] = 0;
      }
    }
  }

  void init(int a[], int n) {
    seg1::n = n;
    h = sizeof(int) * 8 - __builtin_clz(n);
    for (int i = 0; i < n; i++) {
      t[n + i] = a[i];
    }
    for (int i = 0; i < n; i++) {
      _build(n + i);
    }
  }

  void inc(int l, int r, int value) { // increment values in [l, r)
    l += n, r += n;
    int l0 = l, r0 = r;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) _apply(l++, value);
      if (r&1) _apply(--r, value);
    }
    _build(l0);
    _build(r0 - 1);
  }

  int query(int l, int r) { // max on interval [l, r)
    l += n, r += n;
    _push(l);
    _push(r - 1);
    int res = -2e9;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l&1) res = max(res, t[l++]);
      if (r&1) res = max(t[--r], res);
    }
    return res;
  }
}

// range assignment and range sum
// (order of updates important)

// WARNING: we suppose there's a value we never use for modification, in our case it's 0
// In case there's no such value — 
// we would create additional boolean array and refer to it instead of checking d[p] == 0.
namespace seg2 {
  int n; // array size
  int t[2 * N];

  int h = sizeof(int) * 8 - __builtin_clz(n); // height of tree
  int d[N];

  void _calc(int p, int k) {
    if (d[p] == 0) t[p] = t[p<<1] + t[p<<1|1];
    else t[p] = d[p] * k;
  }

  void _apply(int p, int value, int k) {
    t[p] = value * k;
    if (p < n) d[p] = value;
  }

  void _build(int l, int r) {
    int k = 2;
    for (l += n, r += n-1; l > 1; k <<= 1) {
      l >>= 1, r >>= 1;
      for (int i = r; i >= l; --i) _calc(i, k);
    }
  }

  void _push(int l, int r) {
    int s = h, k = 1 << (h-1);
    for (l += n, r += n-1; s > 0; --s, k >>= 1)
      for (int i = l >> s; i <= r >> s; ++i) if (d[i] != 0) {
        _apply(i<<1, d[i], k);
        _apply(i<<1|1, d[i], k);
        d[i] = 0;
      }
  }

  void init(int a[], int n) {
    seg2::n = n;
    h = sizeof(int) * 8 - __builtin_clz(n);
    for (int i = 0; i < n; i++) {
      t[n + i] = a[i];
    }
    _build(0, n);
  }

  void modify(int l, int r, int value) { // assign value in interval [l, r)
    if (value == 0) return;
    _push(l, l + 1);
    _push(r - 1, r);
    int l0 = l, r0 = r, k = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1, k <<= 1) {
      if (l&1) _apply(l++, value, k);
      if (r&1) _apply(--r, value, k);
    }
    _build(l0, l0 + 1);
    _build(r0 - 1, r0);
  }

  int query(int l, int r) { // assign value in interval [l, r)
    _push(l, l + 1);
    _push(r - 1, r);
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l&1) res += t[l++];
      if (r&1) res += t[--r];
    }
    return res;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  int a[n];
  for (int i = 0; i < n; ++i) scanf("%d", a + i);
  seg1::init(a, n);
  seg1::inc(0, 3, 1);
  printf("%d\n", seg1::query(0, 3));
  return 0;
}