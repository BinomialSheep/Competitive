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
    vi X(N), Y(N);
    rep(i, N) cin >> X[i] >> Y[i];
    vi P(M), Q(M);
    rep(i, M) cin >> P[i] >> Q[i];

    /* solve */
    // vector<vector<double>> dist(N + M, vector<double>(N + M));

    vector<vector<double>> dp(1LL << (N + M + 1),
                              vector<double>(N + M + 1, INFTY));

    auto dist = [&](int from, int to, int bit) -> double {
      //
      ll fromX = 0;
      ll fromY = 0;
      if (from != 0) {
        fromX = from < N + 1 ? X[from - 1] : P[from - N - 1];
        fromY = from < N + 1 ? Y[from - 1] : Q[from - N - 1];
      }
      ll toX = 0;
      ll toY = 0;
      if (to != 0) {
        toX = to < N + 1 ? X[to - 1] : P[to - N - 1];
        toY = to < N + 1 ? Y[to - 1] : Q[to - N - 1];
      }
      // if (from == 1 && to == 2) {
      //   debug(fromX, fromY, toX, toY);
      // }

      double ret = abs(fromX - toX) * abs(fromX - toX) +
                   abs(fromY - toY) * abs(fromY - toY);
      ret = sqrt(ret);
      // TODO 現在の速度で割る
      int cnt = 1;
      for (int i = N + 1; i <= (N + M); i++) {
        if (bit >> i & 1) cnt *= 2;
      }
      // debug(from, to, bit, cnt);

      // debug(from, to, ret);
      return ret / cnt;
    };

    rep(i, N + M + 1) {
      if (i == 0) continue;
      dp[1 << i][i] = dist(0, i, 0);
    }

    rep(bit, 1LL << (N + M + 1)) {
      rep(i, N + M + 1) {
        // 訪問済みにiが入っていないのは違反
        if (~bit >> i & 1) continue;
        rep(j, N + M + 1) {
          // 訪問済みなら違反（じゃないけど無駄）
          if (bit >> j & 1) continue;
          int next = bit | 1 << j;
          // debug(next, bit, dp[bit][i], i, j, dist(i, j, bit));
          chmin(dp[next][j], dp[bit][i] + dist(i, j, bit));
        }
      }
    }
    // debug(dp);

    double ans = INFTY;
    for (int i = 0; i < (1 << M); i++) {
      ll bit = ((ll)i << (N + 1)) + (1LL << (N + 1)) - 1;
      // debug(bit, dp[bit][0]);
      chmin(ans, dp[bit][0]);
    }

    /* output */
    cout.precision(10);
    cout << fixed << ans << endl;
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