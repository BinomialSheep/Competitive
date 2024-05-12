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
    int N, L;
    cin >> N >> L;
    vl A(N);
    rep(i, N) cin >> A[i];

    vl B(N);
    rep(i, N) B[i] = -A[i];
    reverse(all(B));
    debug(B);

    /* solve */
    ll diff = 1e18;
    rep(i, N) {
      auto it1 = lower_bound(all(A), L - A[i]);
      auto it2 = lower_bound(all(B), -(L - A[i]));
      if (it1 != A.end()) {
        ll dif1 = *it1 - (L - A[i]);
        chmin(diff, dif1 * 2);
      }
      if (it2 != B.end()) {
        ll dif2 = abs(*it2 + (L - A[i]));
        chmin(diff, dif2 * 2);
      }
    }
    ll ans = 2 * L + diff;
    cout << ans << endl;

    // rep(i, N) rep(j, N) {
    //   // iが左でjが右

    //   if (i == j) continue;
    //   // iが右でjが左

    //   // 両方右

    //   // 両方左
    // }

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