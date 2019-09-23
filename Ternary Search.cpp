// Ternary search
// (Maximizes a unimodal function within a range)
// O(log3(n))

#include <bits/stdc++.h>
using namespace std;

double func(double x) { // function to maximize
	return -1*1*x*x + 2*x +3; 
}

// find maximum value in unimodal function
double ts(double start, double end)
{
    double l = start, r = end;

    for(int i=0; i<200; i++) { // precision = (1/3) ^ iterations
      double l1 = (l*2+r)/3;
      double l2 = (l+2*r)/3;
      //cout<<l1<<" "<<l2<<endl;
      if(func(l1) > func(l2)) r = l2; else l = l1;
    }

    double x = l;
    return func(x);
}
