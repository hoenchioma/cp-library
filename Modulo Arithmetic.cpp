#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;

template <ll MOD = MOD>
inline ll mod_expo(ll a, ll exp) {
  ll res = 1;
  while (exp) {
    if (exp & 1) res = (res * a) % MOD;
    exp = exp >> 1, a = (a * a) % MOD;
  }
  return res;
}

template <ll MOD = MOD>
inline ll mod_inv(ll a) { return mod_expo<MOD>(a, MOD - 2); }

template <ll MOD = MOD>
struct mod_int {
  ll val;

  mod_int() : val() {}
  mod_int(ll a) : val(a % MOD) {}
  explicit operator ll() const { return val; }

  friend inline mod_int operator+(mod_int a, mod_int b) {
  	ll res = a.val + b.val;
    return (res >= MOD ? res - MOD : res);
  }
  friend inline mod_int operator-(mod_int a, mod_int b) {
    ll res = a.val - b.val;
    return (res < 0 ? res + MOD : res);
  }
  friend inline mod_int operator*(mod_int a, mod_int b) {
    return (a.val * b.val) % MOD;
  }
  friend inline mod_int operator/(mod_int a, mod_int b) {
    return (a.val * mod_inv<MOD>(b.val)) % MOD;
  }
};