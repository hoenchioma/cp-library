// Extended Euclidean Algorithm
// calculates gcd(a, b) along with x and y such that a⋅x+b⋅y=gcd(a,b)
// O(log(min(a, b))

int gcd(int a, int b, int & x, int & y) {
  if (a == 0) {
    x = 0;
    y = 1;
    return b;
  }
  int x1, y1;
  int d = gcd(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  return d;
}

// lcm(a, b) = ((a * b) / gcd(a, b)) or (a / gcd(a, b) * b) (to avoid integer overflow)
// gcd of fraction = gcd of numerators / lcm of denominators
