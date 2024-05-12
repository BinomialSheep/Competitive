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
    int A, B, Q;
    cin >> A >> B >> Q;
    vl s(A), t(B);
    rep(i, A) cin >> s[i];
    rep(i, B) cin >> t[i];

    /* solve */
    sort(all(s));
    sort(all(t));

    vl sl(A);

    int ti = 0;
    rep(i, A) {
      while (ti < B && s[i] > t[ti]) {
        ti++;
      }
      sl[i] = ti - 1;
    }

    debug(sl);

    /* output */
    rep(qi, Q) {
      int x;
      cin >> x;
      //
      auto it = upper_bound(all(s), x);
      ll ans = 1e18;
      auto idx2 = -1;
      if (it == s.end()) {
        // 最後まで超えない（xの右に神社はない）
        idx2 = A - 1;
      } else {
        // 道を超える最初のインデックス
        idx2 = (int)(it - s.begin());
      }
      // 神社の左の寺
      auto idx = sl[idx2];
      if (idx != -1) {
        if (x < t[idx]) {
          // 神社 < 寺 < x
          chmin(ans, s[idx2] - x);
        } else {
          // 寺 < x < 神社
          chmin(ans, s[idx2] - x + s[idx2] - t[idx]);
          chmin(ans, x - t[idx] + s[idx2] - t[idx]);
        }
        if (idx2 != 0) {
          // 前神社 < x < 寺
          if (x < t[idx]) {
            chmin(ans, t[idx] - x + t[idx] - s[idx2 - 1]);
            chmin(ans, x - s[idx2 - 1] + t[idx] - s[idx2 - 1]);
          } else if (s[idx2 - 1] < t[idx]) {
            // 前神社 < 寺 < x
            chmin(ans, x - s[idx2 - 1]);
          } else {
            // 寺 < 前神社 < x
            chmin(ans, x - t[idx]);
          }
        }
      } else {
        // 神社の左に寺がない時
        // 神社 < x < 寺
        if (x < t[0]) {
          chmin(ans, s[0] - x + s[0] - s[idx2]);
          chmin(ans, x - t[idx2] + s[0] - t[idx2]);
        } else {
          // 神社 < 寺 < x
          chmin(ans, x - s[idx2]);
        }
      }
      debug(x, idx2, idx);

      cout << ans << '\n';
    }
  }
};

int main() {
  int ts = 2;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}