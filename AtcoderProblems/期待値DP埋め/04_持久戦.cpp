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
    map<int, int> invA;
    rep(i, N) rep(j, 6) invA[A[i][j]] = i;
    vi B;
    rep(i, N) rep(j, 6) B.push_back(A[i][j]);
    sort(rbegin(B), rend(B));

    vector<double> dp(6 * N);
    int idx = -1;
    double mx = -1;

    // サイコロの目とdpのidxのマップ
    map<int, int> mp;
    // あるサイコロを振った時の期待値
    map<int, double> es;

    rep(i, 6 * N) {
      if (i == 0) {
        idx = invA[B[0]];
        mx = B[i];
        mp[B[i]] = i;
        continue;
      }
      // それより上で期待値が1番いいサイコロ（振るべき）のidx
      rep(j, 6) {
        if (A[idx][j] > B[i]) {
          dp[i] += (dp[mp[A[idx][j]]] + 1) / 6;
        }
      }
      mp[B[i]] = i;
      es[invA[B[i]]] += dp[i] / 6;
      if (chmax(mx, es[invA[B[i]]])) idx = invA[B[i]];
    }
    debug(dp);
    debug(invA);

    double ans = 0;
    // idxのサイコロを振るのが最善
    rep(j, 6) ans += dp[mp[A[idx][j]]] / 6;

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