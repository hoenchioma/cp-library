#include <bits/stdc++.h>
using namespace std;

// #include <chrono>
// using namespace std::chrono;
// auto clockStart = high_resolution_clock::now();
// auto timer() {return duration_cast<milliseconds>(high_resolution_clock::now() - clockStart);}

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
// typedef __int128 int128_t;
// typedef unsigned __int128 uint128_t;

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<char, int> pci;
typedef tuple<int, int, int> ti3;
typedef tuple<ll, ll, ll> tl3;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;

#define ff          first
#define ss          second

#define pb(x)       push_back(x)
#define ppb()       pop_back()
#define pf(x)       push_front(x)
#define ppf()       pop_front()
#define mp(x,y)     make_pair(x, y)
#define mk(args...) make_tuple(args...)
#define all(v)     begin(v),end(v)
#define gcd(x, y)   __gcd(x, y)

// pbds and ordered set
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <class T, class cmp = less<T> >
// using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// for fast I/O
#define endl '\n'
#define FASTIO() ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

#ifndef ONLINE_JUDGE
// debugging
  #define WATCH(args...) { string _s = #args; replace(all(_s),',',' '); stringstream _ss(_s); cerr<<"[ "; _debug(istream_iterator<string>(_ss),args); }
  template <class T>
  void _debug(istream_iterator<string> it, T a) { cerr<<*it<<" = "<<a<<" ]"<<endl; }
  template <class T, class... Args>
  void _debug(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<" = "<<a<<", "; _debug(++it, args...); }

  // print array/iterable
  #define PAR(a) { cerr<<"{ "; for(auto it=begin(a);it!=end(a);it++) cerr<<*it<<((it!=prev(end(a)))?", ":" }\n"); }
  // print array of size s
  #define PARS(a,s) { cerr<<"{ "; for(int i=0;i<(s);i++) cerr<<a[i]<<((i!=(s)-1)?", ":" }\n"); }
  // print 2d array size (y * x)
  #define PARS2(a,y,x) { for(int i=0;i<(y);i++) for(int j=0;j<(x);j++) cerr<<a[i][j]<<((j!=(x)-1)?'\t':'\n'); }
#else // turn off debugging functions when OJ
  #define WATCH(args...)
  #define PAR(a)
  #define PARS(a,s)
  #define PARS2(a,x,y)

  #define cerr if(false)cerr
#endif

const int N = 2e5;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const ll INF = INT_MAX-1;

int main() {
  FASTIO();

  
  
  return 0;
}

