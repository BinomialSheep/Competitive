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
    int H, W, K;
    cin >> H >> W >> K;
    vs S(H);
    rep(i, H) cin >> S[i];

    /* solve */
    vvi ans(H, vi(W, 0));

    int color = 0;

    rep(i, H) rep(j, W) {
      if (S[i][j] == '.') continue;
      color++;

      // 左、上、右、下の順で優先する
      int l = j - 1, r = j + 1, t = i - 1, b = i + 1;
      while (l >= 0) {
        if (S[i][l] == '#' || ans[i][l] != 0) break;
        l--;
      }
      l++;
      while (t >= 0) {
        int flag = 0;
        for (int jt = l; jt <= j; jt++) {
          if (S[t][jt] == '#' || ans[t][jt] != 0) {
            flag = 1;
            break;
          }
        }
        if (flag) break;
        t--;
      }
      t++;
      while (r < W) {
        int flag = 0;
        for (int ki = t; ki <= i; ki++) {
          if (S[ki][r] == '#' || ans[ki][r] != 0) {
            flag = 1;
            break;
          }
        }
        if (flag) break;
        r++;
      }
      r--;

      while (b < H) {
        int flag = 0;
        for (int kj = l; kj <= r; kj++) {
          if (S[b][kj] == '#' || ans[b][kj] != 0) {
            flag = 1;
            break;
          }
        }
        if (flag) break;
        b++;
      }
      b--;

      for (int i3 = t; i3 <= b; i3++) {
        for (int j3 = l; j3 <= r; j3++) {
          ans[i3][j3] = color;
        }
      }
    }

    /* output */
    rep(i, H) rep(j, W) printf("%d%c", ans[i][j], j == W - 1 ? '\n' : ' ');
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