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
    int N;
    cin >> N;
    vi T(N), X(N), A(N);
    rep(i, N) cin >> T[i] >> X[i] >> A[i];

    /* solve */
    vvi TXA(1e5 + 1, vi(5));
    rep(i, N) TXA[T[i]][X[i]] = A[i];

    vvl dp(1e5 + 1, vl(5, -1));
    dp[0][0] = 0;
    rep(i, 1e5) {
      // 今いるところ
      rep(j, 5) {
        if (dp[i][j] == -1) continue;
        if (j != 0) {
          if (dp[i + 1][j - 1] == -1) dp[i + 1][j - 1]++;
          chmax(dp[i + 1][j - 1], TXA[i + 1][j - 1] + dp[i][j]);
        }
        if (dp[i + 1][j] == -1) dp[i + 1][j]++;
        chmax(dp[i + 1][j], TXA[i + 1][j] + dp[i][j]);
        if (j != 4) {
          if (dp[i + 1][j + 1] == -1) dp[i + 1][j + 1]++;
          chmax(dp[i + 1][j + 1], TXA[i + 1][j + 1] + dp[i][j]);
        }
      }
    }
    // debug(dp);
    ll ans = 0;
    rep(i, 5) chmax(ans, dp[1e5][i]);

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