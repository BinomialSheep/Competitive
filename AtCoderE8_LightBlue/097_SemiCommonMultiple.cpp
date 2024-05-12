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
  int f(ll n) {
    int ret = 0;
    while (!(n & 1)) {
      n >>= 1;
      ret++;
    }
    return ret;
  }

  void solve() {
    /* input */
    ll N, M;
    cin >> N >> M;
    vl A(N);
    rep(i, N) cin >> A[i];

    /* solve */
    rep(i, N) A[i] /= 2;
    // Aiの2の因数の数は一致していなければならない
    int retF = f(A[0]);
    rep(i, N) {
      if (retF != f(A[i])) {
        cout << 0 << endl;
        return;
      }
      A[i] >>= retF;
    }
    M >>= retF;

    ll lcmA = 1;
    rep(i, N) {
      lcmA = lcm(lcmA, A[i]);
      if (lcmA > M) {
        cout << 0 << endl;
        return;
      }
    }
    debug(lcmA);

    ll ans = M / lcmA;
    ans = (ans + 1) / 2;

    /* output */
    cout << ans << endl;
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