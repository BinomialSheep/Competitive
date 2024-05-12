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
    int N, X;
    ll Y;
    cin >> N >> X >> Y;
    vl A(N), B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];

    /* solve */

    int n2 = 1 << N;
    const ll INF = 4e18;
    vl dp(n2, INF);
    dp[0] = 0;
    rep(bit, n2) {
      // 何番目に置こうとしているか
      int j = __builtin_popcount(bit);
      rep(i, N) {
        // 既に使っていたらダメ
        if (bit >> i & 1) continue;
        // j番目にa[i]を置く
        ll cost = abs(A[i] - B[j]) * X;
        // 下i桁が消えるので、i桁目以上で既に置いた数
        //（= 今置こうとしている数より左で大きい数 = 転倒数）が求まる
        cost += __builtin_popcount(bit >> i) * Y;
        chmin(dp[bit | 1 << i], dp[bit] + cost);
      }
    }

    ll ans = dp[n2 - 1];

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