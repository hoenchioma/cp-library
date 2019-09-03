// Pollard Rho Prime Factorization
// (probabalistic prime factorization of large numbers)
// O(n^(1/4)) 

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

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
        exp = exp >> 1;
        a = modMul(a, a, mod);
    }
    return res;
}

// random number generator (seeded with high precision clock)
std::mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// returns a random number in [a..b]
inline ll randInt(ll a, ll b) {
    return std::uniform_int_distribution <ll> (a, b)(rng);
}

// ******************************* Miller Rabin Primality Test *************************************//
namespace mrpt {
    // returns false if n is composite and returns true if n is probably prime.
    // d is an odd number such that  d*(2^r) = n-1 for some r >= 1 
    inline bool millerTest(ll d, ll n, ll a) {
        // Pick a random number in [2..n-2] 
        // Corner cases make sure that n > 4 
        // ll a = 2 + rand() % (n - 4);
        // ll a = randInt(2, n-2);

        // Compute a^d % n 
        ll x = modExpo(a, d, n);

        if (x == 1 || x == n-1) return true; 
      
        // Keep squaring x while one of the following doesn't happen 
        // (i)   d does not reach n-1 
        // (ii)  (x^2) % n is not 1 
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
    // k is an input parameter that determines accuracy level. Higher value of k indicates more accuracy. 
    bool isPrime(ll n) {
        // Corner cases 
        if (n <= 1 || n == 4)  return false; 
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

// ******************************* Pollard Rho Factorization *************************************//
namespace prho {

    ll pollardRho(ll n) { 
        /* initialize random seed */
        // srand (time(NULL));
      
        /* no prime divisor for 1 */
        if (n == 1) return n;
      
        /* even number means one of the divisors is 2 */
        if (n % 2 == 0) return 2; 
      
        /* we will pick from the range [2, N) */
        // ll x = (rand() % (n-2)) + 2;
        ll x = randInt(2, n-1);
        ll y = x; 
      
        /* the constant in f(x). 
         * Algorithm can be re-run with a different c if it throws failure for a composite. */
        // ll c = (rand() % (n-1)) + 1;
        ll c = randInt(1, n-1); 
      
        /* Initialize candidate divisor (or result) */
        ll d = 1;
      
        /* until the prime factor isn't obtained. If n is prime, return n */
        while (d == 1) {
            /* Tortoise Move: x(i+1) = f(x(i)) */
            x = (modExpo(x, 2, n) + c + n)%n; 
      
            /* Hare Move: y(i+1) = f(f(y(i))) */
            y = (modExpo(y, 2, n) + c + n)%n;
            y = (modExpo(y, 2, n) + c + n)%n;
      
            /* check gcd of |x-y| and n */
            d = __gcd(abs(x-y), n); 

            /* retry if the algorithm fails to find prime factor with chosen x and c */
            if (d == n) return pollardRho(n); 
        }

        return d; 
    }

    ll small_primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    void _pFactorise(ll a, map <ll, int> &pfac) {
        if (a == 1) return;
        if (mrpt::isPrime(a)) pfac[a]++;
        else {
            ll div = pollardRho(a);
            _pFactorise(div, pfac);
            _pFactorise(a/div, pfac);
        }
    }

    void pFactorise(ll a, map <ll, int> &pfac) {
        for (ll i: small_primes) {
            if (i > a) break;
            while (a%i == 0) pfac[i]++, a /= i;
        }
        _pFactorise(a, pfac);
    }
}


int main() {
    // ll num = 888888888888888LL;
    // map <ll, int> a;
    // prho::pFactorise(num, a);
    // for (auto i: a) {
    //     cout << i.first << " " << i.second << endl;
    // }
    map <ll, int> a;
    ll n;
    while (cin >> n) {
        prho::pFactorise(n, a);
        // for (auto i: a) {
        //     printf("%lld %d\n", i.first, i.second);
        // }
        a.clear();
    }
    return 0;
}
