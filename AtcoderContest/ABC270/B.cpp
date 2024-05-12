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
    int X, Y, Z;
    cin >> X >> Y >> Z;

    /* solve */
    int ans = 0;
    if (0 < X && X < Y && X < Z) {
      ans = X;
    } else if (0 < Y && Y < X && Y < Z) {
      ans = -1;
    } else if (0 < Z && Z < X && X < Y) {
      ans = X;
    } else if (0 < Z && Z < Y && Y < X) {
      ans = X;
    } else if (X < 0 && 0 < Y && 0 < Z) {
      ans = -X;
    } else if (Y < 0 && 0 < X && 0 < Z) {
      ans = X;
    } else if (Z < 0 && 0 < X && X < Y) {
      ans = X;
    } else if (Z < 0 && 0 < Y && Y < X) {
      ans = -Z + -Z + X;
    } else if (X < Y && Y < 0 && 0 < Z) {
      ans = -X;
    } else if (X < Z && Z < 0 && 0 < Y) {
      ans = Z + Z + -X;
    } else if (Y < X && X < 0 && 0 > Z) {
      ans = -X;
    } else if (Y < Z && Z < 0 && 0 < X) {
      ans = X;
    } else if (Z < X && X < 0 && 0 < Y) {
      ans = -X;
    } else if (Z < Y && Y < 0 && 0 < X) {
      ans = X;
    } else if (X < Y && Y < Z && Z < 0) {
      ans = -X;
    } else if (X < Z && Z < Y && Y < 0) {
      ans = -1;
    } else if (Y < X && X < Z && Z < 0) {
      ans = -X;
    } else if (Y < Z && Z < X && X < 0) {
      ans = -X;
    } else if (Z < X && X < Y && Y < 0) {
      ans = -1;
    } else if (Z < Y && Y < X && X < 0) {
      ans = -X;
    } else {
      while (true) {
      }
    }

    assert(ans > 0 || ans == -1);

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