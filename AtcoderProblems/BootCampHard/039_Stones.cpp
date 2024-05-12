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
    string S;
    cin >> N >> S;

    /* solve */
    // dp[i][0] := i個目を白としたときのコスト
    vvi dp(N, vi(2, INFTY));
    if (S[0] == '.') dp[0][0] = 0, dp[0][1] = 1;
    if (S[0] == '#') dp[0][0] = 1, dp[0][1] = 0;
    rep(i, N) {
      if (i == 0) continue;
      if (S[i] == '.') {
        chmin(dp[i][0], dp[i - 1][0]);
        chmin(dp[i][1], dp[i - 1][0] + 1);
        chmin(dp[i][1], dp[i - 1][1] + 1);
      } else {
        chmin(dp[i][0], dp[i - 1][0] + 1);
        chmin(dp[i][1], dp[i - 1][0]);
        chmin(dp[i][1], dp[i - 1][1]);
      }
    }
    int ans = min(dp[N - 1][0], dp[N - 1][1]);

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