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
    int H, W;
    cin >> H >> W;
    vvi A(H, vi(W));
    vvi B(H, vi(W));
    rep(i, H) rep(j, W) cin >> A[i][j];
    rep(i, H) rep(j, W) cin >> B[i][j];

    /* solve */
    vector<vector<unordered_set<int>>> dp(H, vector<unordered_set<int>>(W));
    { dp[0][0].insert(0); }

    rep(i, H) rep(j, W) {
      for (auto num : dp[i][j]) {
        if (i < H - 1) {
          dp[i + 1][j].insert(num + A[i][j] - B[i][j]);
          dp[i + 1][j].insert(num + B[i][j] - A[i][j]);
        }
        if (j < W - 1) {
          dp[i][j + 1].insert(num + A[i][j] - B[i][j]);
          dp[i][j + 1].insert(num + B[i][j] - A[i][j]);
        }
      }
    }
    // debug(dp);

    int ans = INFTY;
    for (auto num : dp[H - 1][W - 1]) {
      chmin(ans, abs(num + A[H - 1][W - 1] - B[H - 1][W - 1]));
      chmin(ans, abs(num + B[H - 1][W - 1] - A[H - 1][W - 1]));
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