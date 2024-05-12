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
    int N, X, Y, Z;
    cin >> N >> X >> Y >> Z;
    vi A(N);
    vi B(N);
    rep(i, N) cin >> A[i];
    rep(i, N) cin >> B[i];

    /* solve */
    vi color(N);

    vi C(N);
    rep(i, N) C[i] = A[i];
    sort(C.rbegin(), C.rend());

    int cnt = 0;
    if (X != 0) {
      rep(i, N) {
        rep(j, N) {
          if (A[j] == C[i] && !color[j]) {
            color[j] = 1;
            cnt++;
            if (cnt == X) break;
          }
        }
        if (cnt == X) break;
      }
    }
    debug(color);
    if (Y != 0) {
      cnt = 0;
      rep(i, N) C[i] = B[i];
      sort(C.rbegin(), C.rend());
      rep(i, N) {
        rep(j, N) {
          if (B[j] == C[i] && !color[j]) {
            color[j] = 1;
            cnt++;
            if (cnt == Y) break;
          }
        }
        if (cnt == Y) break;
      }
    }
    debug(color);
    cnt = 0;
    if (Z != 0) {
      rep(i, N) C[i] = A[i] + B[i];
      sort(C.rbegin(), C.rend());
      rep(i, N) {
        rep(j, N) {
          if (A[j] + B[j] == C[i] && !color[j]) {
            color[j] = 1;
            cnt++;
            if (cnt == Z) break;
          }
        }
        if (cnt == Z) break;
      }
    }
    debug(color);

    /* output */
    rep(i, N) {
      if (color[i]) cout << i + 1 << "\n";
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