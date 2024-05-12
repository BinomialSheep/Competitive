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
    int N, M;
    cin >> N >> M;
    vi A(M);
    rep(i, M) cin >> A[i];

    /* solve */
    vi B(N);
    rep(i, N) B[i] = i + 1;
    rep(i, M) { swap(B[A[i] - 1], B[A[i]]); }
    // debug(B);
    vi mp(N + 1);
    rep(i, N) mp[B[i]] = i + 1;
    // debug(mp);
    vi C(N);
    rep(i, N) C[i] = i + 1;
    rep(i, M) {
      int v = 1;
      if (C[A[i] - 1] == 1) {
        v = C[A[i]];
      } else if (C[A[i]] == 1) {
        v = C[A[i] - 1];
      }
      // if (v < 0) {
      //   while (true)
      //     ;
      // }
      // if (v >= N + 1) {
      //   cout << -1 << endl;
      // }
      swap(C[A[i] - 1], C[A[i]]);
      cout << mp[v] << "\n";
    }

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