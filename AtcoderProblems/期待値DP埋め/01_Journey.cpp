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

    /* solve */
    // i頂点が選ばれてからN頂点が選ばれるまでの期待値
    // 初期化はdp[N] = 0なのでOK
    vector<double> dp(N + 1);

    for (int i = N - 1; i >= 0; i--) {
      // i頂点が選ばれてからN頂点が選ばれるまでの期待値は、
      // (i頂点が選ばれてからi+1頂点が選ばれるまでの期待値) +
      // (i+1頂点が選ばれてからN頂点が選ばれるまでの期待値)
      // 後者は計算済み。前者は(N-i)/Nの逆数（無限等比級数を考えるとそうなる）
      dp[i] = (double)N / (N - i) + dp[i + 1];
    }
    // 最初の頂点までは0回の移動のため
    dp[0]--;
    debug(dp);

    /* output */
    cout << setprecision(10) << fixed << dp[0] << endl;
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