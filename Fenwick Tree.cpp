// Fenwick Tree (Binary Indexed Tree)
// find prefix sum (with point update)
// O(log(n))

// one based indexed BIT
struct Fenwick {
  vector <ll> bit;
  int n;

  void init(int n) {
    this->n = n;
    bit.assign(n + 1, 0);
  }

  ll sum(int i) {
    ll res = 0;
    for (; i > 0; i -= i & -i) {
      res += bit[i];
    }
    return res;
  }

  void update(int i, ll del) {
    for (; i <= n; i += i & -i) {
      bit[i] += del;
    }
  }
};