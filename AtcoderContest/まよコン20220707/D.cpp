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
    int N;
    cin >> N;
    vvc S(N, vc(N));
    rep(i, N) rep(j, N) cin >> S[i][j];
    vvc T(N, vc(N));
    rep(i, N) rep(j, N) cin >> T[i][j];

    /* solve */

    // 90°回転をk回
    rep(k, 4) {
      // 範囲を狭めて疑似的に平行移動
      int sl = 300, st = 300, sr = -1, su = -1;
      rep(i, N) rep(j, N) {
        if (S[i][j] == '#') {
          chmin(sl, j);
          chmax(sr, j);
          chmin(st, i);
          chmax(su, i);
        }
      }
      int tl = 300, tt = 300, tr = -1, tu = -1;
      rep(i, N) rep(j, N) {
        if (T[i][j] == '#') {
          chmin(tl, j);
          chmax(tr, j);
          chmin(tt, i);
          chmax(tu, i);
        }
      }
      // 一致判定
      // debug(k, sl, sr, st, su, tl, tr, tt, tu);
      if (sr - sl == tr - tl && su - st == tu - tt) {
        int flag = 1;
        for (int i = st; i <= su; i++) {
          for (int j = sl; j <= sr; j++) {
            int ty = tt + (i - st);
            int tx = tl + (j - sl);
            if (ty >= N || tx >= N) continue;
            if (S[i][j] != T[ty][tx]) flag = 0;
          }
        }
        if (flag) {
          cout << "Yes" << endl;
          return;
        }
      }

      // Tを90°回転させる
      vvc oldT(N, vc(N));
      oldT = T;
      rep(i, N) rep(j, N) { T[j][N - i - 1] = oldT[i][j]; }
      // debug(oldT, T);
    }

    cout << "No" << endl;
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