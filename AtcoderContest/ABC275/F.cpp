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
    int N, M;
    cin >> N >> M;
    vi a(N);
    rep(i, N) cin >> a[i];

    /* solve */
    // dp[m][l][r] := [l, r)でmを作る最小手数
    vvvi dp(M + 1, vvi(N, vi(N, INFTY)));

    auto rec = [&](auto f, int sum, int left, int right) -> int {
      if (dp[sum][left][right] != INFTY) return dp[sum][left][right];
      if (right == left) {
        if (sum == a[left]) {
          dp[sum][left][right] = 0;
        } else {
          return INFTY;
        }
      }
      for(int i = 1; i <= M; i++) {
        // 今回両方使う
        chmin(dp[i][left][right][0], f(f, sum - a[left] - a[right], left + 1, right - 1, 0));
        chmin(dp[i][left][right][0], f(f, sum - a[left] - a[right], left + 1, right - 1, 1));
        chmin(dp[i][left][right][0], f(f, sum - a[left] - a[right], left + 1, right - 1, 2));
        chmin(dp[i][left][right][0], f(f, sum - a[left] - a[right], left + 1, right - 1, 3));
        // 今回左だけ使う
        chmin(dp[i][left][right][1], f(f, sum - a[left], left + 1, right - 1, 0) + 1);
        chmin(dp[i][left][right][1], f(f, sum - a[left], left + 1, right - 1, 1) + 1);
        chmin(dp[i][left][right][1], f(f, sum - a[left], left + 1, right - 1, 2));
        chmin(dp[i][left][right][1], f(f, sum - a[left], left + 1, right - 1, 3));
        // 今回右だけ使う
        chmin(dp[i][left][right][2], f(f, sum - a[right], left + 1, right - 1, 0) + 1);
        chmin(dp[i][left][right][2], f(f, sum - a[right], left + 1, right - 1, 1));
        chmin(dp[i][left][right][2], f(f, sum - a[right], left + 1, right - 1, 2) + 1);
        chmin(dp[i][left][right][2], f(f, sum - a[right], left + 1, right - 1, 3));
        // 今回両方使わない
        chmin(dp[i][left][right][3], f(f, sum - a[right], left + 1, right - 1, 0) + 2);
        chmin(dp[i][left][right][3], f(f, sum - a[right], left + 1, right - 1, 1) + 1);
        chmin(dp[i][left][right][3], f(f, sum - a[right], left + 1, right - 1, 2) + 1);
        chmin(dp[i][left][right][3], f(f, sum - a[right], left + 1, right - 1, 3));
    };

    /* output */
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