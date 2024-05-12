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

// ビッドDP、bit DP、桁DP
// 巡回セールスマン
// bitDPのちょっと効率いいヤツ

struct Solver {
  void solve() {
    /* input */
    int N;
    cin >> N;
    vi X(N), Y(N), Z(N);
    rep(i, N) cin >> X[i] >> Y[i] >> Z[i];

    /* solve */

    vvi dist(N, vi(N));
    rep(i, N) rep(j, N) {
      dist[i][j] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]) + max(0, Z[j] - Z[i]);
    }

    // どこから始めても同じなので、0から始めたことにする
    vvi dp(1 << N, vi(N, INFTY));
    rep(i, N) {
      // 最初は0からどこかに移動する
      if (i == 0) continue;
      dp[1 << i][i] = dist[0][i];
    }

    rep(bit, 1 << N) {
      // iから次の頂点に配る
      rep(i, N) {
        // 訪問済みにiが入っていないのは違反
        if (~bit >> i & 1) continue;
        rep(j, N) {
          // 訪問済みなら違反
          if (bit >> j & 1) continue;
          int next = bit | 1 << j;
          chmin(dp[next][j], dp[bit][i] + dist[i][j]);
        }
      }
    }

    int fullBit = (1 << N) - 1;
    int ans = dp[fullBit][0];

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