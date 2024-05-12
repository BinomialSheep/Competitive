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
    int n;
    cin >> n;
    vi pre(n), in(n);
    rep(i, n) cin >> pre[i], pre[i]--;
    rep(i, n) cin >> in[i], in[i]--;

    /* solve */
    vi ni(n);
    rep(i, n) ni[in[i]] = i;

    vi l(n), r(n);
    auto f = [&](auto f2, int lp, int li, int len) -> int {
      if (len == 0) return 0;
      int root = pre[lp];
      int i = ni[root];
      // 範囲外ならダメ
      if (i < li || i >= li + len) return -1;
      //
      int ls = i - li, rs = len - 1 - ls;
      l[root] = f2(f2, lp + 1, li, ls);
      r[root] = f2(f2, lp + 1 + ls, li + ls + 1, rs);

      if (l[root] == -1 || r[root] == -1) return -1;
      // 1-indexedに戻すための+1
      return root + 1;
    };

    if (f(f, 0, 0, n) != 1) {
      cout << -1 << endl;
      return;
    }
    rep(i, n) printf("%d %d\n", l[i], r[i]);

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