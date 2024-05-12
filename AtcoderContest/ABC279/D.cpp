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
    ll A, B;
    cin >> A >> B;

    using ld = long double;

    // 目的関数(最小化したい)
    auto f = [&](double x) { return (double)x * B + (double)A / sqrt(x + 1); };

    // 左側
    double low = 0;
    // 右側
    double high = 1e16;

    // 500回繰り返す
    int cnt = 1000;
    while (cnt--) {
      double c1 = (low * 2 + high) / 3;
      double c2 = (low + high * 2) / 3;
      // もしf(c2)のほうが良い(小さい)なら、駄目な方lowを更新する
      // debug(c1, c2);
      if (f(c1) > f(c2))
        low = c1;
      else
        high = c2;
    }
    double ans = 1e18;
    for (ll i = -10; i <= 10; i++) {
      ll m = (ll)(low + i);
      if (m < 0) continue;
      chmin(ans, f(m));
    }

    cout << fixed << setprecision(20) << ans << endl;

    /* solve */

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