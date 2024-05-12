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
    int sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    /* solve */
    string ans = "";

    rep(i, tx - sx) ans.push_back('R');
    rep(i, ty - sy) ans.push_back('U');
    rep(i, tx - sx) ans.push_back('L');
    rep(i, ty - sy) ans.push_back('D');
    ans.push_back('D');
    rep(i, tx - sx + 1) ans.push_back('R');
    rep(i, ty - sy + 1) ans.push_back('U');
    ans.push_back('L');
    ans.push_back('U');
    rep(i, tx - sx + 1) ans.push_back('L');
    rep(i, ty - sy + 1) ans.push_back('D');
    ans.push_back('R');

    int r = 0, l = 0, u = 0, d = 0;
    rep(i, (int)ans.size()) {
      if (ans[i] == 'R') r++;
      if (ans[i] == 'L') l++;
      if (ans[i] == 'U') u++;
      if (ans[i] == 'D') d++;
    }
    assert(r == l);
    assert(u == d);
    assert((int)ans.size() == 4 * (ty - sy + tx - sx) + 8);

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