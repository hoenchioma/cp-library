// Matrix Exponentiation
// O(k^3 log(n)), k = size of matrix, n = exponent

#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;

#define ff first
#define ss second

const int MOD = 1e9;

template <class T> struct Matrix {
    vector<T> arr;
    size_t row, col;

    Matrix(size_t r, size_t c, T val = 0)
        : arr(r * c, val), row(r), col(c) {}

    inline T& operator()(size_t r, size_t c) {
        assert(r < row and c < col);
        return arr[col * r + c];
    }

    inline T operator()(size_t r, size_t c) const {
        assert(r < row and c < col);
        return arr[col * r + c];
    }

    void fill(T val) {
        arr.assign(row * col, val);
    }

    static Matrix<T> identity(size_t n) {
        Matrix<T> ans(n, n);
        for (size_t i = 0; i < n; i++) {
            ans(i, i) = 1;
        }
        return ans;
    }

    Matrix<T> modMul(const Matrix& a, size_t mod) const {
        assert(col == a.row);
        Matrix<T> ans(row, a.col);

        for (size_t i = 0; i < ans.row; i++) {
            for (size_t j = 0; j < ans.col; j++) {
                ans(i, j) = 0;
                for (size_t k = 0; k < col; k++) {
                    ans(i, j) = (ans(i, j) + ((*this)(i, k) * a(k, j)) % mod) % mod;
                }
            }
        }

        return ans;
    }

    Matrix<T> pow(size_t exp, size_t mod) const {
        assert(row == col);
        Matrix<T> ans = identity(row), self(*this);

        while (exp > 0) {
            if (exp & 1) {
                ans = ans.modMul(self, mod);
            }
            exp >>= 1;
            self = self.modMul(self, mod);
        }

        return ans;
    }

    void print() const {
        for (size_t i = 0; i < row; i++) {
            for (size_t j = 0; j < col; j++) {
                cout << (*this)(i, j) << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    // using matrix exponentiation to solve 
    // f(n) = c1 * f(n-1) + c2 * f(n-2) + ... + ck * f(n-k)
    // given f(i); i <= k

    while (t--) {
        int k;
        cin >> k;

        Matrix<ll> base(k, 1), mid(k, k);

        for (int i = 0; i < k; i++) {
            cin >> base(i, 0);
        }
        for (int i = 0; i < k; i++) {
            cin >> mid(k - 1, k - i - 1);
        }
        for (int i = 0; i < k - 1; i++) {
            mid(i, i + 1) = 1;
        }

        ll n;
        cin >> n;

        ll ans = (mid.pow(n-1, MOD).modMul(base, MOD))(0, 0);

        cout << ans << endl;
    }

    return 0;
}
