// Miller Rabin Primality Test
// (probabalistic primality test)
// O(k (log(n))^3)

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// modular multiplication
inline ll modMul(ll a, ll b, ll mod) {
  a %= mod; b %= mod;
  // if b is larger swap a and b
  if (b > a) swap(a, b);
  if (b == 0) return 0;
  // if numbers are small enough, do normal multiplication
  if (a < (LLONG_MAX / b)) return (a*b)%mod;
  ll res = 0;
  while (b) {
    if (b & 1) {
      res += a;
      if (res >= mod) res -= mod;
    }
    b >>= 1;
    a <<= 1;
    if (a >= mod) a -= mod;
  }
  return res;
  // return ((__int128)a*b)%mod;
}

// modular exponentiation: O(log(exp))
inline ll modExpo(ll a, ll exp, ll mod) { 
  ll res = 1;
  a = a % mod;
  while (exp) {
    if (exp & 1) {
      res = modMul(res, a, mod);
    }
    exp >>= 1;
    a = modMul(a, a, mod);
  } 
  return res;
}

namespace mrpt {
  // returns false if n is composite and returns true if n is probably prime.
  // d is an odd number such that d*(2^r) = n-1 for some r >= 1 
  inline bool millerTest(ll d, ll n, ll a) {
    // Pick a random number in [2..n-2] 
    // Corner cases make sure that n > 4 
    // ll a = 2 + rand() % (n - 4);
    // ll a = randInt(2, n-2);

    // Compute a^d % n 
    ll x = modExpo(a, d, n);

    if (x == 1 || x == n-1) return true; 
   
    // Keep squaring x while one of the following doesn't happen 
    // (i)  d does not reach n-1 
    // (ii) (x^2) % n is not 1 
    // (iii) (x^2) % n is not n-1 
    while (d != n-1) { 
      // x = (x * x) % n;
      x = modExpo(x, 2, n); 
      d *= 2; 
      if (x == 1) return false; 
      if (x == n-1) return true; 
    }
    return false; 
  }
  // confirmed bases for numbers upto 10^18
  ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
   
  // It returns false if n is composite and returns true if n is probably prime.
  bool isPrime(ll n) {
    // Corner cases 
    if (n <= 1 || n == 4) return false; 
    if (n <= 3) return true; 
    
    // Find r such that n = 2^r * d + 1 for some r >= 1
    // __builtin_clzll finds the highest power of 2 that divides into n-1
    ll d = (n-1) >> __builtin_ctzll(n-1);
    
    // check for all the known bases
    for (ll p: bases) {
      if (p > n-2) break;
      if (!millerTest(d, n, p)) return false;
    }
    return true; 
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  ll n;
  while (cin >> n) {
    assert(mrpt::isPrime(n));
  }
  return 0;
}