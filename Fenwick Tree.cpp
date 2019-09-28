// Fenwick Tree (Binary Indexed Tree)
// find prefix sum (with point update)
// O(log(n))

// solution to: LOJ 1112

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

int main() {
    int t, cc = 1;
    scanf("%d", &t);

    BIT bit;

    while (t--) {
        int n, q;
        scanf("%d %d", &n, &q);

        bit.init(n);

        for (int i = 1; i <= n; i++) {
            int x; scanf("%d", &x);
            bit.update(i, x);
        }

        printf("Case %d:\n", cc++);

        for (int i = 0; i < q; i++) {
            int com;
            scanf("%d", &com);

            if (com == 1) {
                int x; scanf("%d", &x);
                x++;
                ll amount = bit.sum(x) - bit.sum(x-1);
                printf("%lld\n", amount);
                bit.update(x, -amount);
            } else if (com == 2) {
                int x, v;
                scanf("%d %d", &x, &v);
                x++;
                bit.update(x, v);
            } else {
                int x, y;
                scanf("%d %d", &x, &y);
                x++, y++;
                printf("%lld\n", bit.sum(y) - bit.sum(x-1));
            }
        }
    }

    return 0;
}