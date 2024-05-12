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
    int X, Y, A, B, C;
    cin >> X >> Y >> A >> B >> C;
    vi p(A);
    rep(i, A) cin >> p[i];
    vi q(B);
    rep(i, B) cin >> q[i];
    vi r(C);
    rep(i, C) cin >> r[i];

    /* solve */

    sort(p.rbegin(), p.rend());
    sort(q.rbegin(), q.rend());
    sort(r.rbegin(), r.rend());

    vi pp(X);
    rep(i, X) pp[X - 1 - i] = p[i];
    vi qq(Y);
    rep(i, Y) qq[Y - 1 - i] = q[i];

    int pd = 0, qd = 0;
    rep(i, C) {
      if (pd == X && qd == Y) break;
      int pa = INFTY, qa = INFTY;
      if (pd != X) pa = pp[pd];
      if (qd != Y) qa = qq[qd];
      if (pa >= r[i] && qa >= r[i]) break;
      if (pa >= qa) {
        qq[qd] = r[i];
        qd++;
      } else {
        pp[pd] = r[i];
        pd++;
      }
    }

    ll ans = 0;
    for (auto pa : pp) ans += pa;
    for (auto qa : qq) ans += qa;
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