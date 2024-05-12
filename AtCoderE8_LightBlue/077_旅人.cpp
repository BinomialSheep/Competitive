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
    int n, m;
    cin >> n >> m;
    vi s(n - 1);
    rep(i, n - 1) cin >> s[i];
    vi a(m);
    rep(i, m) cin >> a[i];

    /* solve */
    int mod = 1e5;
    using mint = modint;
    mint::set_mod(mod);

    // 0から頂点nまでの距離
    vector<mint> dist(n);
    rep(i, n - 1) dist[i + 1] = (dist[i] + s[i]);

    mint ans = 0;
    int now = 0;
    rep(i, m) {
      debug(now);
      if (a[i] >= 0) {
        ans += dist[now + a[i]] - dist[now];
      } else {
        ans += dist[now] - dist[now + a[i]];
      }
      now = now + a[i];
    }

    /* output */
    cout << ans.val() << endl;
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