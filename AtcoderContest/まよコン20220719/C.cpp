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
    int r1, c1, r2, c2;
    cin >> r1 >> c1 >> r2 >> c2;

    /* solve */
    if (r1 == r2 && c1 == c2) {
      cout << 0 << endl;
      return;
    }
    // 一手で到達可能
    if (abs(r1 - r2) + abs(c1 - c2) <= 3) {
      cout << 1 << endl;
      return;
    }
    if (r1 + c1 == r2 + c2 || r1 - c1 == r2 - c2) {
      cout << 1 << endl;
      return;
    }
    // 二手で到達可能
    for (int y = r1 - 3; y <= r1 + 3; y++) {
      for (int x = c1 - 3; x <= c1 + 3; x++) {
        if (abs(r1 - y) + abs(c1 - x) <= 3) {
          if (abs(y - r2) + abs(x - c2) <= 3) {
            cout << 2 << endl;
            return;
          }
          if (y + x == r2 + c2 || y - x == r2 - c2) {
            cout << 2 << endl;
            return;
          }
        }
      }
    }
    for (int y = r2 - 3; y <= r2 + 3; y++) {
      for (int x = c2 - 3; x <= c2 + 3; x++) {
        if (abs(r2 - y) + abs(c2 - x) <= 3) {
          if (abs(y - r1) + abs(x - c1) <= 3) {
            cout << 2 << endl;
            return;
          }
          if (y + x == r1 + c1 || y - x == r1 - c1) {
            cout << 2 << endl;
            return;
          }
        }
      }
    }
    if (abs(r2 - r1) % 2 == abs(c2 - c1) % 2) {
      cout << 2 << endl;
      return;
    }

    cout << 3 << endl;

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