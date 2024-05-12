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
    vs S(10);
    rep(i, 10) cin >> S[i];

    /* solve */
    int A, B, C, D;
    for (int a = 1; a <= 10; a++) {
      for (int b = a; b <= 10; b++) {
        for (int c = 1; c <= 10; c++) {
          for (int d = c; d <= 10; d++) {
            vs T(10, string(10, '.'));
            for (int i = a - 1; i <= b - 1; i++) {
              for (int j = c - 1; j <= d - 1; j++) {
                T[i][j] = '#';
              }
            }
            int flag = 1;
            rep(k, 10) if (S[k] != T[k]) flag = 0;
            if (flag) A = a, B = b, C = c, D = d;
          }
        }
      }
    }

    /* output */
    cout << A << " " << B << endl;
    cout << C << " " << D << endl;
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