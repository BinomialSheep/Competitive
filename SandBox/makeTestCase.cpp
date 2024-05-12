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

// 0以上UINT_MAX(0xffffffff)以下の整数をとる乱数 xorshift
// https://ja.wikipedia.org/wiki/Xorshift
static uint32_t randXor() {
  static uint32_t x = 123456789;
  static uint32_t y = 362436069;
  static uint32_t z = 521288629;
  static uint32_t w = 88675123;
  uint32_t t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

struct Solver {
  int makeRnd(int min_, int max_) {
    // 閉区間
    if (max_ == min_) return max_;
    return randXor() % (max_ - min_) + min_;
  }

  void solve() {
    /* input */
    int N, M, R;
    // 2 <= N <= 200
    N = makeRnd(2, 15);
    // 1 <= M <= N * (N-1)/2
    M = makeRnd(N, N * (N - 1) / 2);
    // 2 <= R <= min(8, N)
    R = makeRnd(2, min(8, N));
    //
    vi r(R);
    rep(i, R) r[i] = i + 1;
    //
    vi A(M), B(M), C(M);
    rep(i, M) {
      A[i] = makeRnd(1, N);
      B[i] = makeRnd(1, N);
      C[i] = makeRnd(1, 100);
    }
    rep(i, N - 1) {
      A[i] = i + 1;
      B[i] = i + 2;
      C[i] = 1000;
    }

    /* solve */

    /* output */
    printf("%d %d %d\n", N, M, R);
    rep(i, R) cout << r[i] << " ";
    cout << endl;
    rep(i, M) printf("%d %d %d\n", A[i], B[i], C[i]);
    cout << endl;
  }
};

int main() {
  int ts = 10;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}