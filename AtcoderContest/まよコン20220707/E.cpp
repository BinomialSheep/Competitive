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
    vi X(N), Y(N), Z(N);
    rep(i, N) cin >> X[i] >> Y[i] >> Z[i];

    /* solve */
    vvi dist(N, vi(N));
    rep(i, N) rep(j, N) {
      dist[i][j] = abs(X[i] - X[j]) + abs(Y[i] - Y[j]) + max(0, Z[j] - Z[i]);
    }

    // dp[bit][start][i] :=
    // 訪問状態がbitで、startから始めて、今iにいる時の最小値
    vvvi dp((1 << N), vvi(N, vi(N, INFTY)));
    rep(i, N) dp[1 << i][i][i] = 0;

    rep(bit, 1 << N) {
      rep(start, N) {
        rep(i, N) {
          // 探索済み状態に、今いるiが含まれていないケースは違反
          if (!(bit & (1 << i))) continue;
          // 各未訪問の頂点に配る
          rep(j, N) {
            // 訪問済みなら無視
            if (bit & (1 << j)) continue;
            // 更新
            int nexBit = bit | (1 << j);
            chmin(dp[nexBit][start][j], dp[bit][start][i] + dist[i][j]);
          }
        }
      }
    }

    int fullBit = (1 << N) - 1;
    ll ans = INFTY;
    // まだ始点に戻っていないので、始点に戻った分を足しながら数える
    rep(start, N) {
      rep(i, N) { chmin(ans, (ll)dp[fullBit][start][i] + dist[i][start]); }
    }

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