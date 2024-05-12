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
    int N, M;
    cin >> N >> M;
    vi C(M), cost(M);
    vvi idol(M), p(M);
    rep(i, M) {
      cin >> C[i] >> cost[i];
      rep(j, C[i]) {
        int a, b;
        cin >> a >> b;
        --a;
        idol[i].push_back(a);
        p[i].push_back(b);
      }
    }
    /* solve */
    // ある状態から、全部引いた状態までに必要な金額の期待値
    // i人目を持っていたらi桁目が0（ループを簡単にするため）
    vector<double> dp(1 << N, INFTY);
    // 初期化
    dp[0] = 0;
    rep(bit, 1 << N) {
      rep(i, M) {
        // ガチャiを引く
        double now = 0;
        int notNew = 0;
        rep(j, C[i]) {
          if (bit & (1 << idol[i][j])) {
            // 持ってない
            int bit2 = bit & ~(1 << idol[i][j]);  // 持ってる状態
            now += dp[bit2] * p[i][j];
          } else {
            // 持ってる
            notNew += p[i][j];
          }
        }
        if (notNew == 100) continue;
        double X = (double)(now / 100 + cost[i]) / (1 - (double)notNew / 100);
        chmin(dp[bit], X);
      }
    }
    /* output */
    printf("%.10f\n", dp[(1 << N) - 1]);
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