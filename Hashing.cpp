// Hashing

// solution to: https://algo.codemarshal.org/contests/icpc-dhaka-19-preli/problems/A

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

const int N = 1200009, INF = INT_MAX-1;
const ll MOD = 1e9 + 9, P = 31;

ll modExpo(ll a, ll exp, ll mod) {
    ll res = 1;
    a = a % mod;
    while (exp) {
        if (exp & 1) res = (res*a) % mod;
        exp = exp >> 1;
        a = (a*a) % mod;
    }
    return res;
}

string s, p;
ll hsh[N], phsh[N], inv[N]; // inv[i] = (P ^ -i) mod MOD

inline ll shash(int i, int j) { // compute hash of s[i..j]
    ll res = hsh[j] - (i > 0? hsh[i-1]: 0);
    if (res < 0) res += MOD;
    return (res * inv[i]) % MOD;
}

inline ll phash(int i, int j) { // compute hash of p[i..j]
    ll res = phsh[j] - (i > 0? phsh[i-1]: 0);
    if (res < 0) res += MOD;
    return (res * inv[i]) % MOD;
}

inline bool almosteq(int i, int pn, int k) { // return whether number of mismatch is less than or equal to k
    int pi = 0, miss = 0;
    while (pn > 0 and miss <= k) {
        if (shash(i, i+pn-1) == phash(pi, pi+pn-1)) {
            break;
        }
        int l = 0, h = pn-1;
        while (l < h) {
            int m = (l + h)/2;
            if (shash(i, i+m) == phash(pi, pi+m)) l = m+1;
            else h = m;
        }
        i += l+1, pi += l+1, pn -= l+1;
        miss++;
    }
    return miss <= k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    s.reserve(N);
    p.reserve(N);

    inv[0] = 1, inv[1] = modExpo(P, MOD-2, MOD);
    for (ll i = 2; i < N; i++) {
        inv[i] = (inv[i-1] * inv[1]) % MOD;
    }

    int t, cc = 1;
    cin >> t;

    while (t--) {
        int k;
        cin >> s >> p >> k;

        int n = s.length(), pn = p.length();

        for (ll i = 0, j = 1; i < n; i++, j *= P, j %= MOD) {
            hsh[i] = ((i > 0? hsh[i-1]: 0) + (s[i] - 'a' + 1) * j) % MOD;
        }

        for (ll i = 0, j = 1; i < pn; i++, j *= P, j %= MOD) {
            phsh[i] = ((i > 0? phsh[i-1]: 0) + (p[i] - 'a' + 1) * j) % MOD;
        }

        ll ans = 0;
        for (int i = 0, j = pn-1; j < n; i++, j++) {
            if (almosteq(i, pn, k)) ans++;
        }

        cout << "Case " << cc++ << ": " << ans << endl;
    }

    return 0;
}
