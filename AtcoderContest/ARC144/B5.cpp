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
    int N, a, b;
    cin >> N >> a >> b;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */

    int ng = 1e9 + 10;
    int ok = 0;
    while (abs(ok - ng) > 1) {
      int mid = (ok + ng) / 2;

      // mid以上にできるかはんていする
      ll cnt1 = 0;
      ll cnt2 = 0;
      rep(i, N) {
        //
        if (A[i] < mid) {
          // 何回足せばC以上になるか
          cnt1 += (mid - A[i]) / a;
          if ((mid - A[i]) % a) cnt1++;
        }
        if (A[i] > mid) {
          cnt2 += (A[i] - mid) / b;
        }
      }

      if (cnt2 >= cnt1) {
        ok = mid;
      } else {
        ng = mid;
      }
    }
    /* output */
    cout << ok << endl;
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