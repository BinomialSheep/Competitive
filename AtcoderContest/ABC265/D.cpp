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
    int N;
    ll P, Q, R;
    cin >> N >> P >> Q >> R;
    vi A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    vl prefix(N + 1);
    rep(i, N) { prefix[i + 1] = A[i] + prefix[i]; }
    debug(prefix);

    rep(i, N - 2) {
      // xの開始位置はi+1

      // yの位置
      auto ity = lower_bound(all(prefix), prefix[i] + P);
      if (ity == prefix.end()) continue;
      if (prefix[i] + P < *ity) continue;

      // zの位置
      auto itz = lower_bound(all(prefix), *ity + Q);
      if (itz == prefix.end()) continue;
      if (*ity + Q < *itz) continue;

      // wの位置
      auto itw = lower_bound(all(prefix), *itz + R);
      if (itw == prefix.end()) continue;
      if (*itz + R < *itw) continue;

      cout << "Yes" << endl;
      return;
    }
    cout << "No" << endl;

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