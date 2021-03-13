#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

// rational number implementation
struct rat {
  ll num, den;
  rat(ll num, ll den): num(num), den(den) {}
  rat(ll a): rat(a, 1) {}

  rat& norm() {
    ll g = __gcd(num, den);
    num /= g, den /= g;
    return (*this);
  }

  friend rat operator+(rat a, rat b) {
    return rat(a.num * b.den + b.num * a.den, a.den * b.den).norm();
  }
  friend rat operator-(rat a, rat b) {
    return rat(a.num * b.den - b.num * a.den, a.den * b.den).norm();
  }
  friend rat operator*(rat a, rat b) {
    return rat(a.num * b.num, a.den * b.den).norm();
  }
  friend rat operator/(rat a, rat b) {
    return rat(a.num * b.den, a.den * b.num).norm();
  }

  friend bool operator<(rat a, rat b) {
    return a.num * b.den < b.num * a.den;
  }
  friend bool operator>(rat a, rat b) { 
    return a.num * b.den > b.num * a.den; 
  }
  friend bool operator==(rat a, rat b) { 
    return a.num * b.den == b.num * a.den; 
  }
  friend bool operator<=(rat a, rat b) {
    return a.num * b.den <= b.num * a.den;
  }
  friend bool operator>=(rat a, rat b) {
    return a.num * b.den >= b.num * a.den;
  }

  friend ll floor(rat a) { return a.num / a.den; }
  friend ll ceil(rat a) { return (a.num + a.den - 1) / a.den; }

  explicit operator ll() { return num / den; }
  explicit operator ld() { return (ld) num / den; }
};