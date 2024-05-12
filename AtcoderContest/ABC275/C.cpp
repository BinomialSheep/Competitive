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
    rep(i, 8) rep(j, 8) {
      if (S[i][j] == '.') continue;
      for (int i2 = i + 1; i2 < 9; i2++) {
        for (int j2 = j + 1; j2 < 9; j2++) {
          if (S[i][j2] == '.') continue;
          if (S[i2][j] == '.') continue;
          if (S[i2][j2] == '.') continue;
          ans++;
        }
      }
    }
    rep(i, 7) rep(j, 7) {
      if (S[i][j] == '.') continue;
      for (int j2 = j + 2; j2 < 9; j2 += 2) {
        if (S[i][j2] == '.') continue;
        int d = (j2 - j) / 2;
        if (i - d < 0 || i + d > 9) continue;
        if (j - d < 0 || j + d > 9) continue;
        if (S[i - d][j + d] == '.') continue;
        if (S[i + d][j + d] == '.') continue;
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