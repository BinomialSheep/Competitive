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
    int N, M, K;
    cin >> N >> M >> K;
    vi A(M), B(M), C(M);
    rep(i, M) {
      cin >> A[i] >> B[i] >> C[i];
      --A[i], --B[i];
    }
    vi E(K);
    rep(i, K) {
      cin >> E[i];
      --E[i];
    }

    /* solve */

    map<int, ll> dp;
    dp[0] = 0;
    rep(i, K) {
      // debug(E[i], A[E[i]], B[E[i]], C[E[i]]);
      // debug(dp);
      // Eを使う
      if (dp.count(A[E[i]])) {
        // debug(v, dp.count(B[E[i]]));
        if (dp.count(B[E[i]]) == 0) {
          dp[B[E[i]]] = dp[A[E[i]]] + C[E[i]];
        } else {
          chmin(dp[B[E[i]]], dp[A[E[i]]] + C[E[i]]);
        }
      }
      // Eを使わない
    }

    /* output */
    if (dp.count(N - 1) == 0) {
      cout << -1 << endl;
    } else {
      cout << dp[N - 1] << endl;
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