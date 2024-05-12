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
    int N;
    cin >> N;
    vvi A(N, vi(6));
    rep(i, N) rep(j, 6) cin >> A[i][j];

    /* solve */
    vi B;
    rep(i, N) rep(j, 6) B.push_back(A[i][j]);
    sort(all(B));
    {
      // 座標圧縮
      map<int, int> mp;
      rep(i, 6 * N) mp[B[i]] = i, B[i] = i;
      rep(i, N) rep(j, 6) A[i][j] = mp[A[i][j]];
    }
    map<int, int> invA;
    rep(i, N) rep(j, 6) invA[A[i][j]] = i;

    int bestDice = -1;
    vector<double> dp(6 * N);

    for (int i = 6 * N - 1; i >= 0; i--) {
      if (i == 6 * N - 1) {
        dp[i] = 1;
        continue;
      }
      // どのサイコロを振るべきか
      // 1. i+1が出るサイコロを振る
      double diceE = 0;
      int dice = invA[B[i + 1]];
      rep(j, 6) {
        if (A[dice][j] > B[i]) {
          diceE += dp[A[dice][j]] / 6;
        }
      }
      diceE += 1;
      // 2. i+1において最善だったサイコロを振る
      if (bestDice != -1) {
        double diceE2 = 0;
        rep(j, 6) {
          if (A[bestDice][j] > B[i]) {
            diceE2 += dp[A[bestDice][j]] / 6;
          }
        }
        diceE2 += 1;
        if (chmax(diceE, diceE2)) dice = bestDice;
      }
      bestDice = dice;
      // そのサイコロを振った時の期待値
      dp[i] = diceE;
    }
    debug(dp);

    // どのサイコロからスタートするかって非自明なのかな……
    double ans = 0;
    rep(i, N) {
      double now = 0;
      rep(j, 6) { now += dp[A[i][j]] / 6; }
      now += 1;
      chmax(ans, now);
    }

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