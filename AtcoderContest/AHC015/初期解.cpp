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
#include <atcoder/all>
using namespace atcoder;
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
  ll calcScore(vvi &maze) {
    ll ret = 0;

    vi cnt(3);
    rep(i, 10) rep(j, 10) {
      debug(i, j, maze[i][j]);
      assert(1 <= maze[i][j] && maze[i][j] <= 3);
      cnt[maze[i][j] - 1]++;
    }

    dsu uf(100);
    rep(i, 10) rep(j, 10) {
      if (j < 9) {
        if (maze[i][j] == maze[i][j + 1]) uf.merge(i * 10 + j, i * 10 + j + 1);
      }
      if (i < 9) {
        if (maze[i][j] == maze[i + 1][j]) uf.merge(i * 10 + j, i * 10 + j + 10);
      }
    }

    for (auto g : uf.groups()) {
      ret += g.size() * g.size();
    }
    ll denominator = 0;
    rep(i, 3) denominator += cnt[i] * cnt[i];
    ret = ret * 1e6 / denominator;
    return ret;
  }

  void tiltF(vvi &maze) {
    rep(j, 10) {
      rep(k, 10) {
        rep(i, 9) {
          if (maze[i][j] == 0 && maze[i + 1][j] != 0) {
            maze[i][j] = maze[i + 1][j];
            maze[i + 1][j] = 0;
          }
        }
      }
    }
    cout << "F" << endl;
  }

  void solve() {
    /* input */
    vvi maze(10, vi(10));
    vi f(100);
    rep(i, 100) cin >> f[i];

    /* solve */
    rep(i, 100) {
      int pos;
      cin >> pos;
      debug(pos);
      // debug用
      // while (maze[pos / 10][pos % 10] != 0) {
      //   pos++;
      //   if (pos == 100) pos = 0;
      // }
      maze[pos / 10][pos % 10] = f[i];
      //
      if (i != 100) tiltF(maze);
      // debug(maze);
    }
    debug(maze);
    debug(calcScore(maze));
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