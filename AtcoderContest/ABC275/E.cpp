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
  void solve() {
    /* input */
    int N, M, K;
    cin >> N >> M >> K;

    using mint = modint998244353;
    /* solve */
    vector<vector<mint>> dp(K, vector<mint>(N + 1));
    rep(i, K) dp[i][N] = 1;
    //
    for (int j = N - M; j <= N - 1; j++) {
      dp[K - 1][j] = 1;
      dp[K - 1][j] /= M;
    }

    //
    for (int i = K - 2; i >= 0; i--) {
      rep(j, N) {
        for (int d = 1; d <= M; d++) {
          if (j + d <= N) {
            dp[i][j] += dp[i + 1][j + d];
          } else {
            dp[i][j] += dp[i + 1][N - (j + d - N)];
          }
        }
        dp[i][j] /= M;
      }
    }
    // rep(i, K) rep(j, N + 1) { debug(i, j, dp[i][j].val()); }

    /* output */
    cout << dp[0][0].val() << endl;
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