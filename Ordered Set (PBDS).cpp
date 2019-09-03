// Policy Based Data Structures (Ordered Set)

#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <class T, class cmp = less<T> >
using ordered_set = tree<T, null_type, cmp, rb_tree_tag, tree_order_statistics_node_update>;

// order_of_key(x): index of x in sorted array (if it exists) / number of values strictly less than x 
// find_by_order(x): (returns iterator) value at index x in sorted array

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	// using ordered_set like multiset

	ordered_set < pair <int, int> > a;
	int time = 0;
	a.insert({7, time++});
	a.insert({4, time++});
	a.insert({5, time++});
	a.insert({4, time++});
	a.insert({6, time++});
	a.insert({5, time++});
	a.insert({1, time++});

	for (int i = 0; i < (int) a.size(); i++) {
		cout << a.find_by_order(i)->first << endl;
	}
	cout << endl;
	cout << a.order_of_key({5, 0}) << endl; // lower bound
	cout << a.order_of_key({5, time}) << endl; // upper bound
    
    return 0;
}
