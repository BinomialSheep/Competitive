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
    int T;
    cin >> T;

    rep(ti, T) {
      /* input */
      int N, M;
      cin >> N >> M;
      vl x(N), y(N);
      rep(i, N) cin >> x[i] >> y[i];
      /* solve */
      vl B(N);
      rep(i, N) B[i] = x[i] * y[i];
      rep(i, N - 1) B[i + 1] += B[i];
      vl A(N);
      rep(i, N) {
        ll ai = x[i];
        if (i != 0) ai += B[i - 1];
        ll ni = y[i];
        ll li = B[i];
        if (ni % 2) {
          A[i] = (ai + li) / 2 * ni;
        } else {
          A[i] = ni / 2 * (ai + li);
        }
        if (i != 0) A[i] += A[i - 1];
      }
      ll INFTYL = 5e18;
      ll ans = -INFTYL;
      rep(i, N) chmax(ans, A[i]);

      // Bの途中でプラスからマイナスに転じている可能性がある
      rep(i, N - 1) {
        if (B[i] <= 0) continue;
        if (B[i + 1] >= 0) continue;
        if (x[i + 1] >= 0) continue;
        if (B[i] + x[i + 1] <= 0) continue;
        // 途中でプラスからマイナスに転じているパターン
        ll last = B[i];
        ll ai = x[i + 1] + last;
        ll ni = last / (-x[i + 1]);
        ll li = last % (-x[i + 1]);
        ll a2;
        if (ni % 2) {
          a2 = (ai + li) / 2 * ni;
        } else {
          a2 = ni / 2 * (ai + li);
        }
        // debug(i, ai, ni, li, a2);
        chmax(ans, A[i] + a2);
      }

      //全部がマイナスのケースのフォロー
      chmax(ans, x[0]);

      debug(B);
      debug(A);
      /* output */
      cout << ans << "\n";
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