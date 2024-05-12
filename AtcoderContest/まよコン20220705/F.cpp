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
    string S;
    cin >> S;

    using mint = modint1000000007;
    /* solve */
    int N = (int)S.size();
    vector<vector<mint>> dp(N + 1, vector<mint>(4));
    dp[0][0] = 1;
    rep(i, (int)S.size()) {
      rep(j, 4) dp[i + 1][j] += dp[i][j];
      if (S[i] == 'A') {
        dp[i + 1][1] += dp[i][0];
      } else if (S[i] == 'B') {
        dp[i + 1][2] += dp[i][1];
      } else if (S[i] == 'C') {
        dp[i + 1][3] += dp[i][2];
      } else {
        rep(j, 4) dp[i + 1][j] += 2 * dp[i][j];
        dp[i + 1][1] += dp[i][0];
        dp[i + 1][2] += dp[i][1];
        dp[i + 1][3] += dp[i][2];
      }
    }
    rep(i, N + 1) rep(j, 4) { debug(i, j, dp[i][j].val()); }

    int ans = dp[N][3].val();
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