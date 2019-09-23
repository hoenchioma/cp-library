// Fenwick Tree (Binary Indexed Tree)
// find prefix sum (with point update)
// O(log(n))

// solution to: LOJ 1085

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 1e5 + 9, MOD = 1000000007;

ll a[N];

struct BIT {
    vector <ll> bit;
    int n;

    void init(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    ll sum(int i) {
        ll res = 0;
        for (; i >= 0; i = (i & (i + 1)) - 1) {
            res += bit[i];
            res %= MOD;
        }
        return res;
    }

    void update(int i, ll del) {
        for (; i < n; i = i | (i + 1)) {
            bit[i] += del;
            bit[i] %= MOD;
        }
    }
};

int main() {
    int t, cc = 1;
    scanf("%d", &t);

    BIT bit;

    while (t--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            scanf("%lld", a + i);
        }

        vector<ll> b(a, a + n);
        sort(b.begin(), b.end(), greater<ll>{});
        b.erase(unique(b.begin(), b.end()), b.end());

        bit.init(b.size());

        ll ans = 0;
        for (int i = n-1; i >= 0; i--) {
            int ind = lower_bound(b.begin(), b.end(), a[i], greater<ll>{}) - b.begin();
            ll res = bit.sum(ind-1) + 1;
            res %= MOD;
            bit.update(ind, res);
            ans += res;
            ans %= MOD;
        }

        printf("Case %d: %lld\n", cc++, ans);
    }
    return 0;
}