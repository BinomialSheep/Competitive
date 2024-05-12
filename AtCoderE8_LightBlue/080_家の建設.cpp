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
  void solve() {
    /* input */
    int H, W, K;
    ll V;
    cin >> H >> W >> K >> V;
    vvl A(H, vl(W));
    rep(i, H) rep(j, W) cin >> A[i][j];

    /* solve */
    vvl sum(H + 1, vl(W + 1));
    rep(i, H) rep(j, W) sum[i + 1][j + 1] =
        sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + A[i][j];
    debug(sum);

    ll ans = 0;
    rep(y1, H) rep(x1, W) rep(y2, H + 1) rep(x2, W + 1) {
      // (x1, y1)から(x2-1, y2-1)までを購入する
      if (x1 > x2 || y1 > y2) continue;
      if (x2 == 0 || y2 == 0) continue;

      ll cost = sum[y2][x2] + sum[y1][x1] - sum[y1][x2] - sum[y2][x1];
      int area = (x2 - x1) * (y2 - y1);
      cost += (ll)area * K;
      if (cost <= V) chmax(ans, (ll)area);
    }
    /* output */
    cout << ans << endl;
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