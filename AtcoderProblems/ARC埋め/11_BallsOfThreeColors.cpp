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
    int T;
    cin >> T;
    rep(ti, T) {
      /* input */
      vi C(3);
      rep(i, 3) cin >> C[i];
      sort(all(C));

      /* solve */
      int ans = INFTY;

      if (C[0] % 3 == C[1] % 3) {
        // まずC[0]を0にする
        // 0, C[1] - C[0], 2 * C[0] + C[2]
        int now = C[0];
        // C[0]とC[1]の数を揃える
        // (C[1]-C[0])/3をXとすると
        // 2X, 2X, 2*C[0]+C[2]-X
        now += (C[1] - C[0]) / 3;
        // C[0]とC[1]を0にする
        // 0, 0, 2*C[0]+C[2]+3X
        // 0, 0, C[0]+C[1]+C[2]
        now += (C[1] - C[0]) / 3 * 2;
        chmin(ans, now);
      }
      if (C[1] % 3 == C[2] % 3) {
        int now = C[1];
        now += (C[2] - C[1]) / 3;
        now += (C[2] - C[1]) / 3 * 2;
        chmin(ans, now);
      }
      if (C[2] % 3 == C[0] % 3) {
        int now = C[0];
        now += (C[2] - C[0]) / 3;
        now += (C[2] - C[0]) / 3 * 2;
        chmin(ans, now);
      }

      /* output */
      cout << (ans == INFTY ? -1 : ans) << "\n";
    }
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