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
    vs S(9);
    rep(i, 9) cin >> S[i];

    /* solve */
    int ans = 0;
    rep(i, 9) rep(j, 9) {
      if (S[i][j] == '.') continue;
      rep(i2, 9) rep(j2, 9) {
        if (i2 > i) continue;
        if (j2 <= j) continue;
        if (i2 < 0 || i2 > 8) continue;
        if (j2 < 0 || j2 > 8) continue;
        if (S[i2][j2] == '.') continue;
        int i3 = i2 + abs(j2 - j);
        int j3 = j2 + abs(i2 - i);
        if (i3 < 0 || i3 > 8) continue;
        if (j3 < 0 || j3 > 8) continue;
        if (S[i3][j3] == '.') continue;
        int i4 = i + abs(j2 - j);
        int j4 = j + abs(i2 - i);
        if (i4 < 0 || i4 > 8) continue;
        if (j4 < 0 || j4 > 8) continue;
        if (S[i4][j4] == '.') continue;
        ans++;
      }
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