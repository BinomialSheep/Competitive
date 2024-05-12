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
  ll llMin(ll a, ll b) {
    if (a <= b)
      return a;
    else
      return b;
  }
  ll llMax(ll a, ll b) {
    if (a >= b)
      return a;
    else
      return b;
  }

  void solve() {
    /* input */
    int A, B, Q;
    cin >> A >> B >> Q;
    ll INF = 1e18;
    ll INF2 = 2e18;
    vl s(A + 4);
    rep(i, A) cin >> s[i];
    vl t(B + 4);
    rep(i, B) cin >> t[i];
    s[A] = t[B] = -INF;
    s[A + 1] = t[B + 1] = -INF2;
    s[A + 2] = t[B + 2] = INF;
    s[A + 3] = t[B + 3] = INF2;

    /* solve */
    sort(all(s));
    sort(all(t));

    rep(qi, Q) {
      ll x;
      cin >> x;

      int si = lower_bound(all(s), x) - s.begin();
      int ti = lower_bound(all(t), x) - t.begin();

      ll ans = 4e18;
      chmin(ans, x - llMin(s[si - 1], t[ti - 1]));
      chmin(ans, llMax(s[si], t[ti]) - x);
      chmin(ans, s[si] - x + s[si] - t[ti - 1]);
      chmin(ans, x - t[ti - 1] + s[si] - t[ti - 1]);
      chmin(ans, t[ti] - x + t[ti] - s[si - 1]);
      chmin(ans, x - s[si - 1] + t[ti] - s[si - 1]);

      cout << ans << endl;
    }

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