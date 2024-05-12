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
    int H, W;
    cin >> H >> W;
    vs G(H);
    rep(i, H) cin >> G[i];

    /* solve */
    vvi visited(H, vi(W));

    int y = 0;
    int x = 0;

    while (true) {
      if (visited[y][x]) {
        cout << -1 << endl;
        return;
      } else {
        visited[y][x] = 1;
      }
      if (G[y][x] == 'U') {
        if (y == 0) {
          printf("%d %d\n", y + 1, x + 1);
          return;
        }
        --y;
      } else if (G[y][x] == 'D') {
        if (y == H - 1) {
          printf("%d %d\n", y + 1, x + 1);
          return;
        }
        ++y;
      } else if (G[y][x] == 'L') {
        if (x == 0) {
          printf("%d %d\n", y + 1, x + 1);
          return;
        }
        --x;
      } else {
        if (x == W - 1) {
          printf("%d %d\n", y + 1, x + 1);
          return;
        }
        ++x;
      }
      // debug(y, x);
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