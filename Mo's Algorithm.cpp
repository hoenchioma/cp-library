// Mo's Algorithm
// (Offline query processing using sqrt decomposition)
// O(n sqrt(n))

// Solution to: CF 86D

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define ff first
#define ss second

typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;

const int MAX = 2e5 + 9, MAX2 = 1e6 + 9;

int a[MAX], fre[MAX2];
vector <pair <pii, int>> qq;
vector <pair <ll, int>> final;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}

	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		qq.push_back({{l, r}, i});
	}

	int seg = sqrt(n);

	sort(qq.begin(), qq.end(), [=](pair <pii, int> a, pair <pii, int> b) {
		if (a.ff.ff/seg == b.ff.ff/seg) {
			return a.ff.ss < b.ff.ss;
		}
		return a.ff.ff/seg < b.ff.ff/seg;
	});

	int cl = 0, cr = 0;
	ll ans = 0;
	for (int i = 0; i < m; i++) {
		int l = qq[i].ff.ff, r = qq[i].ff.ss;
		while (cl > l) {
			cl--;
			ans -= (ll) fre[a[cl]]*fre[a[cl]]*a[cl];
			fre[a[cl]]++;
			ans += (ll) fre[a[cl]]*fre[a[cl]]*a[cl];
		}
		while (cr < r) {
			cr++;
			ans -= (ll) fre[a[cr]]*fre[a[cr]]*a[cr];
			fre[a[cr]]++;
			ans += (ll) fre[a[cr]]*fre[a[cr]]*a[cr];
		}
		while (cl < l) {
			ans -= (ll) fre[a[cl]]*fre[a[cl]]*a[cl];
			fre[a[cl]]--;
			ans += (ll) fre[a[cl]]*fre[a[cl]]*a[cl];
			cl++;
		}
		while (cr > r) {
			ans -= (ll) fre[a[cr]]*fre[a[cr]]*a[cr];
			fre[a[cr]]--;
			ans += (ll) fre[a[cr]]*fre[a[cr]]*a[cr];
			cr--;
		}
		final.push_back({ans, qq[i].ss});
	}
	sort(final.begin(), final.end(), [](pair <ll, int> a, pair <ll, int> b) {
		return a.ss < b.ss;
	});

	for (auto i: final) {
		cout << i.ff << endl;
	}

	return 0;
}
