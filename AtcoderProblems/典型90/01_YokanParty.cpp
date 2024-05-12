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
    int N, L, K;
    cin >> N >> L >> K;
    vi A(N + 1);
    rep(i, N) cin >> A[i];
    A[N] = L - A[N - 1];
    for (int i = N - 1; i >= 1; i--) A[i] -= A[i - 1];
    debug(A);

    /* solve */
    auto f = [&](int v) {
      int num = 0;
      ll now = 0;
      rep(i, N + 1) {
        now += A[i];
        if (now >= v) {
          num++;
          now = 0;
        }
      }
      return num >= K + 1;
    };

    int wa = INFTY;
    int ac = 0;
    while (abs(ac - wa) > 1) {
      int wj = (wa + ac) / 2;
      debug(wj, f(wj));
      if (f(wj)) {
        ac = wj;
      } else {
        wa = wj;
      }
    }
    cout << ac << endl;
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