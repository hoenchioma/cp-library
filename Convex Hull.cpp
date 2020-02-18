// Convex Hull
// Time: O(n log(n))

namespace hull {
  using pt = pair<ll, ll>;

  #define x first
  #define y second

  inline ll darea(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y);
  }

  inline bool cw(pt a, pt b, pt c) {
    return darea(a, b, c) < 0;
  }

  inline bool ccw(pt a, pt b, pt c) {
    return darea(a, b, c) > 0;
  }

  vector<pt> convex_hull(vector<pt> a) {
    if (a.size() == 1) return a;

    sort(a.begin(), a.end());
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.emplace_back(p1);
    down.emplace_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
      if (i == (int)a.size() - 1 || cw(p1, a[i], p2)) {
        while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i])) {
          up.pop_back();
        }
        up.emplace_back(a[i]);
      }
      if (i == (int)a.size() - 1 || ccw(p1, a[i], p2)) {
        while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i])) {
          down.pop_back();
        }
        down.emplace_back(a[i]);
      }
    }

    vector<pt> res;
    for (int i = 0; i < (int)up.size(); i++) res.emplace_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--) res.emplace_back(down[i]);

    return res;
  }
}
