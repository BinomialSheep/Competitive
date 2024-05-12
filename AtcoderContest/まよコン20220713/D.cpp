#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
using vvvi = vector<vector<vector<int>>>;
using pii = pair<int, int>;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
// #define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

struct Solver {
  ll dist(ll x1, ll x2, ll y1, ll y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  }

  void solve() {
    /* input */
    int N;
    cin >> N;
    ll sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;
    vl x(N), y(N), r(N);
    rep(i, N) cin >> x[i] >> y[i] >> r[i];

    /* solve */
    dsu du(N);
    int start = -1;
    int end = -1;

    rep(i, N) rep(j, N) {
      //
      ll d = dist(x[i], x[j], y[i], y[j]);
      ll r1 = r[i];
      ll r2 = r[j];

      // debug(j, i, d, r1, r2);

      // 離れすぎ
      if ((r1 + r2) * (r1 + r2) < d) continue;
      // 内包
      if (d < (r1 - r2) * (r1 - r2)) continue;

      // debug("merge");

      du.merge(i, j);

      //
    }
    rep(i, N) {
      if (dist(x[i], sx, y[i], sy) == r[i] * r[i]) start = i;
      if (dist(x[i], tx, y[i], ty) == r[i] * r[i]) end = i;
    }

    if (start == -1 || end == -1) {
      cout << "No" << endl;
      return;
    }

    if (du.same(start, end)) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }

    // dsu

    /* output */
  }
};

int main() {
  int ts = 1;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}