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
    ll L, R;
    cin >> N >> L >> R;
    vl A(N);
    rep(i, N) cin >> A[i];
    /* solve */
    vl preA(N + 1);
    rep(i, N) { preA[i + 1] = preA[i] + A[i]; }

    // debug(preA);
    // お尻の累積和
    vl changeA(N + 1);
    for (int i = N - 1; i >= 0; i--) {
      if (i == N - 1) {
        changeA[i] = A[i];
        chmin(changeA[i], R);
      } else {
        changeA[i] = changeA[i + 1] + A[i];
        chmin(changeA[i], R * (N - i));
      }
    }
    debug(changeA);

    /* solve */
    ll ans = (1LL << 60);
    // 真ん中を尺取りする
    rep(i, N + 1) {
      // iよりも左を変える(iを含めない)
      ll ls = L * i;
      ll sum = ls + changeA[i];
      // debug(ls, changeA[i]);
      chmin(ans, sum);
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