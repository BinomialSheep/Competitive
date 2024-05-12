#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (n); ++i)
using P = pair<int, int>;

// Coodinate Compression
// https://youtu.be/fR3W5IcBGLQ?t=8550
template <typename T = int>
struct CC {
  bool initialized;
  vector<T> xs;
  CC() : initialized(false) {}
  void add(T x) { xs.push_back(x); }
  void init() {
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    initialized = true;
  }
  int operator()(T x) {
    if (!initialized) init();
    return upper_bound(xs.begin(), xs.end(), x) - xs.begin() - 1;
  }
  T operator[](int i) {
    if (!initialized) init();
    return xs[i];
  }
  int size() {
    if (!initialized) init();
    return xs.size();
  }
};

int main() {
  int n;
  cin >> n;
  map<int, vector<P>> ps;
  CC bs;
  rep(i, n) {
    vector<int> a(3);
    rep(j, 3) cin >> a[j];
    sort(a.begin(), a.end());
    ps[a[0]].emplace_back(a[1], a[2]);
    bs.add(a[1]);
  }

  const int INF = 1001001001;
  auto op = [](int a, int b) { return min(a, b); };
  auto e = []() { return INF; };
  segtree<int, op, e> t(bs.size());
  for (auto [a, bc] : ps) {
    for (auto [b, c] : bc) {
      b = bs(b);
      if (t.prod(0, b) < c) {
        cout << "Yes" << endl;
        return 0;
      }
    }
    for (auto [b, c] : bc) {
      b = bs(b);
      t.set(b, op(c, t.get(b)));
    }
  }

  cout << "No" << endl;
  return 0;
}
