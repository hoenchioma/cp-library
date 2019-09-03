#include <bits/stdc++.h>
using namespace std;

// #include <chrono>
// using namespace std::chrono;
// auto clockStart = high_resolution_clock::now();
// auto timer() {return duration_cast<milliseconds>(high_resolution_clock::now() - clockStart);}

#define endl '\n'

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, ll> pll;
typedef pair<char, int> pci; 

#define ff          first
#define ss          second

#define pb(x)       push_back(x)
#define ppb()       pop_back()
#define pf(x)       push_front(x)
#define ppf()       pop_front()
#define mp(x, y)    make_pair(x, y)
#define full(v)     begin(v),end(v)
#define gcd(x, y)   __gcd(x, y)

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// template <class T, class cmp = less<T> >
// using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// debugging
#ifndef ONLINE_JUDGE
    #define debug(args...) { string _s = #args; replace(full(_s),',',' '); stringstream _ss(_s); cerr<<"[ "; _debug(istream_iterator<string>(_ss),args); }
    template <class T>
    void _debug(istream_iterator<string> it, T a) { cerr<<*it<<" = "<<a<<" ]"<<endl; }
    template <class T, class... Args>
    void _debug(istream_iterator<string> it, T a, Args... args) { cerr<<*it<<" = "<<a<<", "; _debug(++it, args...); }

    #define parr(a) { cout<<"{ "; for(auto it=begin(a);it!=end(a);it++) cerr<<*it<<((it!=prev(end(a)))?", ":" }\n"); }
    #define parrs(a,s) { cout<<"{ "; for(int i=0;i<(s);i++) cerr<<a[i]<<((i!=(s)-1)?", ":" }\n"); }
#else
    #define debug(args...)
    #define parr(a)
    #define parrs(a,s)
#endif

const int N = 2e5;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const ll INF = INT_MAX-1;

int main() 
{
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {

        //printf("Case %d: %d\n",i+1,);
    }
    
    return 0;
}

