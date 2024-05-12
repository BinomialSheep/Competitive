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
    int N, Ma, Mb;
    cin >> N >> Ma >> Mb;
    vi a(N), b(N), c(N);
    rep(i, N) cin >> a[i] >> b[i] >> c[i];

    /* solve */
    vvvi dp(N + 1, vvi(401, vi(401, INFTY)));
    dp[0][0][0] = 0;

    rep(i, N) {
      rep(j, 401) rep(k, 401) {
        if (dp[i][j][k] != INFTY) {
          chmin(dp[i + 1][j + a[i]][k + b[i]], dp[i][j][k] + c[i]);
          chmin(dp[i + 1][j][k], dp[i][j][k]);
        }
      }
    }
    int ans = INFTY;
    rep(j, 401) rep(k, 401) {
      if (j != 0 && j * Mb == k * Ma) {
        chmin(ans, dp[N][j][k]);
      }
    }

    /* output */
    if (ans == INFTY) {
      cout << -1 << endl;
    } else {
      cout << ans << endl;
    }
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