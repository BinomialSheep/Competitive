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
    int N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];

    using mint = modint998244353;
    using vmint = vector<mint>;
    using vvmint = vector<vmint>;
    using vvvmint = vector<vvmint>;
    /* solve */
    mint ans = 0;

    for (int i = 1; i <= N; i++) {
      // dp[N][i+1]
      vvvmint dp(N + 1, vvmint(i + 1, vmint(i)));
      dp[0][0][0] = 1;
      rep(j, N) {
        rep(k, i + 1) rep(h, i) {
          if (dp[j][k][h] == 0) continue;
          // 選ぶ
          if (k != i) {
            // h + A[j]
            int h2 = (h + A[j]) % i;
            dp[j + 1][k + 1][h2] += dp[j][k][h];
          }
          // 選ばない
          dp[j + 1][k][h] += dp[j][k][h];
        }
      }

      ans += dp[N][i][0];
      // debug(i, ans.val());
    }
    // rep(l, N + 1) rep(j, N + 1) rep(k, i + 1) debug(i, j, k,
    // dp[l][j][k].val());

    /* output */
    cout << ans.val() << endl;
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