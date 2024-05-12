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

double dp[301][301][301];

struct Solver {
  void solve() {
    /* input */
    int N;
    cin >> N;
    vi a(N);
    rep(i, N) cin >> a[i];

    /* solve */
    dp[0][0][0] = 0;
    rep(k, N + 1) {
      rep(j, N + 1) {
        rep(i, N + 1) {
          if (i == 0 && j == 0 && k == 0) continue;
          // 1個の皿がi枚、2個の皿がj枚、3個の皿がk枚、0個の皿がN-i-j-k枚
          if (i + j + k > N) continue;
          // 1を足しておく
          dp[i][j][k] = 1;
          // 1個の皿を引く確率はi/N
          if (i != 0) dp[i][j][k] += dp[i - 1][j][k] * i / N;
          // 2個の皿を引く
          if (j != 0) dp[i][j][k] += dp[i + 1][j - 1][k] * j / N;
          // 3個の皿を引く
          if (k != 0) dp[i][j][k] += dp[i][j + 1][k - 1] * k / N;
          // 0枚の皿を(N - i - j - k) / Nで引く分を考慮
          double p = (double)(N - i - j - k) / N;
          dp[i][j][k] /= (1 - p);
        }
      }
    }
    // rep(i, N + 1) {
    //   rep(j, N + 1) {
    //     rep(k, N + 1) { debug(i, j, k, dp[i][j][k]); }
    //   }
    // }

    vi cnt(3);
    rep(i, N) cnt[a[i] - 1]++;
    double ans = dp[cnt[0]][cnt[1]][cnt[2]];
    /* output */
    printf("%.10f\n", ans);
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