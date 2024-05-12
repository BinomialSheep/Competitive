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
    vs S(4);
    rep(i, 4) cin >> S[i];

    /* solve */
    vector<double> dp(1 << 16, 1e9);
    dp[0] = 0;

    vs board(6);
    rep(i, 6) board[i] = "......";
    rep(i, 4) rep(j, 4) board[i + 1][j + 1] = S[i][j];

    rep(bit, 1 << 16) {
      rep(i, 4) rep(j, 4) {
        // i+1, j+1を狙う
        double now = 0;
        int out = 5;
        if (board[i + 1][j + 1] == '#') {
          int k = i * 4 + j;
          if (bit & (1 << k)) {
            now += dp[bit & ~(1 << k)] / 5;
            out--;
          }
        }
        if (board[i + 1][j] == '#') {
          int k = i * 4 + j - 1;
          if (bit & (1 << k)) {
            now += dp[bit & ~(1 << k)] / 5;
            out--;
          }
        }
        if (board[i + 1][j + 2] == '#') {
          int k = i * 4 + j + 1;
          if (bit & (1 << k)) {
            now += dp[bit & ~(1 << k)] / 5;
            out--;
          }
        }
        if (board[i][j + 1] == '#') {
          int k = (i - 1) * 4 + j;
          if (bit & (1 << k)) {
            now += dp[bit & ~(1 << k)] / 5;
            out--;
          }
        }
        if (board[i + 2][j + 1] == '#') {
          int k = (i + 1) * 4 + j;
          if (bit & (1 << k)) {
            now += dp[bit & ~(1 << k)] / 5;
            out--;
          }
        }
        now += 1;
        if (out != 5) chmin(dp[bit], now * (5.0 / (5 - out)));
      }
    }

    /* output */
    int ansBit = 0;
    rep(i, 4) rep(j, 4) if (S[i][j] == '#') ansBit += 1 << (i * 4 + j);
    debug(ansBit);
    printf("%.10f\n", dp[ansBit]);
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