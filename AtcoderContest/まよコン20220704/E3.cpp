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
    string S;
    cin >> S;
    int K;
    cin >> K;

    /* solve */
    int N = (int)S.length();
    vvvi dp(N + 1, vvi(K + 1, vi(2)));
    dp[0][0][1] = 1;

    rep(i, N) rep(j, K + 1) rep(k, 2) {
      rep(d, 10) {
        if (j == K && d != 0) continue;
        if (k == 1 && d > S[i] - '0') continue;
        if (k == 1 && d == S[i] - '0') {
          if (d == 0) {
            dp[i + 1][j][1] += dp[i][j][k];
          } else {
            dp[i + 1][j + 1][1] += dp[i][j][k];
          }
        } else {
          if (d == 0) {
            dp[i + 1][j][0] += dp[i][j][k];
          } else {
            dp[i + 1][j + 1][0] += dp[i][j][k];
          }
        }
      }
    }
    // rep(i, N + 1) rep(j, K + 1) debug(dp[i][j]);

    ll ans = dp[N][K][0] + dp[N][K][1];

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