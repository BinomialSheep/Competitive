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
  double dp[101][101][101];

  void solve() {
    /* input */
    int A, B, C;
    cin >> A >> B >> C;

    /* solve */
    rep(i, 101) rep(j, 101) rep(k, 101) dp[i][j][k] = 0;
    for (int a = 99; a >= 0; a--) {
      for (int b = 99; b >= 0; b--) {
        for (int c = 99; c >= 0; c--) {
          if (a == 0 && b == 0 && c == 0) continue;
          // if (a == 99 && b == 99 && c == 99) {
          //   dp[a][b][c] = 1;
          //   continue;
          // }
          // aを引く
          dp[a][b][c] += (double)a / (a + b + c) * (1 + dp[a + 1][b][c]);
          // bを引く
          dp[a][b][c] += (double)b / (a + b + c) * (1 + dp[a][b + 1][c]);
          // cを引く
          dp[a][b][c] += (double)c / (a + b + c) * (1 + dp[a][b][c + 1]);
        }
      }
    }

    /* output */
    printf("%.10f\n", dp[A][B][C]);
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