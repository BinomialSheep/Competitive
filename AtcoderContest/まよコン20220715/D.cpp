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

using bs = bitset<63>;

struct Solver {
  void solve() {
    int T;
    cin >> T;

    rep(ti, T) {
      /* input */
      ll ai, si;
      cin >> ai >> si;

      bs a = ai, s = si;

      /* solve */
      // debug(ti, a, s);

      // 繰り上がりフラグ
      bool isNo = false;
      int flag = 0;
      rep(i, 63) {
        if (flag) {
          if (a[i]) {
            // s[i] = 1, x[i] = 1, y[i] = 1, flag = 1で確定
            if (!s[i]) {
              isNo = true;
            }
            flag = 1;
          } else {
            if (s[i]) {
              // s[i] = 1, x[i] = 0, y[i] = 0, flag = 0
              flag = 0;
            } else {
              // s[i] = 0, x[i] = 0, y[i] = 1, flag = 1
              flag = 1;
            }
          }
        } else {
          if (a[i]) {
            // s[i] = 0, x[i] = 1, y[i] = 1, flag = 0で確定
            if (s[i]) {
              isNo = true;
            }
            flag = 1;
          } else {
            if (s[i]) {
              // s[i] = 1, x[i] = 0, y[i] = 1, flag = 0
              flag = 0;
            } else {
              // s[i] = 0, x[i] = 0, y[i] = 0, flag = 0
              flag = 0;
            }
          }
        }
      }
      // 最後に繰り上がることはないダメ
      if (flag) isNo = true;

      /* output */
      if (isNo) {
        cout << "No" << endl;
      } else {
        cout << "Yes" << endl;
      }
    }
  }
};

int main() {
  int ts = 2;
  rep(ti, ts) {
    Solver solver;
    solver.solve();
  }
  return 0;
}