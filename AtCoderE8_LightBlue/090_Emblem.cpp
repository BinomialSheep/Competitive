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
// #include <atcoder/all>
// using namespace atcoder;
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
  int calcrr(int x1, int x2, int y1, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
  }

  void solve() {
    /* input */
    int N, M;
    cin >> N >> M;
    vi x(N), y(N), r(N);
    rep(i, N) cin >> x[i] >> y[i] >> r[i];
    vi x2(M), y2(M);
    rep(i, M) cin >> x2[i] >> y2[i];

    /* solve */
    // r2[i] := i個目の円が取れる最大の半径（の2乗）
    vector<double> r2(M, (double)INFTY);
    // 不変半径円との比較
    rep(i, N) rep(j, M) {
      int rr = calcrr(x[i], x2[j], y[i], y2[j]);
      debug(i, j, rr);
      chmin(r2[j], sqrt(rr) - r[i]);
    }
    // 可変半径円同士の比較
    rep(i, M) rep(j, i) {
      int rr = calcrr(x2[i], x2[j], y2[i], y2[j]);
      debug(i, j, rr);
      chmin(r2[j], sqrt(rr) / 2);
    }

    double ans = INFTY;
    rep(i, M) chmin(ans, r2[i]);

    rep(i, N) chmin(ans, (double)r[i]);

    /* output */
    printf("%.10f\n", ans);
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
