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
    int M;
    cin >> N >> M;

    /* solve */
    set<pair<int, int>> st;
    rep(i, N + 1) rep(j, N + 1) {
      if (i * i + j * j == M) {
        st.emplace(i, j);
      }
    }

    vvi maze(N, vi(N, INFTY));

    queue<pair<int, int>> q;
    q.emplace(0, 0);
    maze[0][0] = 0;

    while (!q.empty()) {
      auto [y, x] = q.front();
      q.pop();

      for (auto [dy, dx] : st) {
        if (y + dy < N && x + dx < N) {
          if (chmin(maze[y + dy][x + dx], maze[y][x] + 1)) {
            q.emplace(y + dy, x + dx);
          }
        }
        if (y + dy < N && x - dx >= 0) {
          if (chmin(maze[y + dy][x - dx], maze[y][x] + 1)) {
            q.emplace(y + dy, x - dx);
          }
        }
        if (0 <= y - dy && x + dx < N) {
          if (chmin(maze[y - dy][x + dx], maze[y][x] + 1)) {
            q.emplace(y - dy, x + dx);
          }
        }
        if (0 <= y - dy && x - dx >= 0) {
          if (chmin(maze[y - dy][x - dx], maze[y][x] + 1)) {
            q.emplace(y - dy, x - dx);
          }
        }
      }
    }
    rep(i, N) rep(j, N) {
      if (maze[i][j] == INFTY) maze[i][j] = -1;
    }

    /* output */
    rep(i, N) {
      rep(j, N) { cout << maze[i][j] << " "; }
      cout << "\n";
    }
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