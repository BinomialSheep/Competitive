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
    vs S(H);
    rep(i, H) cin >> S[i];

    /* solve */
    int ans = 0;
    vi dx = {-1, 0, 0, 1};
    vi dy = {0, -1, 1, 0};
    rep(i, H) rep(j, W) {
      if (S[i][j] == '#') continue;
      queue<pii> q;
      q.emplace(i, j);
      vvi visited(H, vi(W, -1));
      visited[i][j] = 0;
      while (!q.empty()) {
        auto p = q.front();
        q.pop();
        rep(k, 4) {
          int y = p.first + dy[k];
          int x = p.second + dx[k];
          if (y < 0 || H <= y) continue;
          if (x < 0 || W <= x) continue;
          if (visited[y][x] != -1) continue;
          if (S[y][x] == '#') continue;
          visited[y][x] = visited[p.first][p.second] + 1;
          q.emplace(y, x);
        }
      }
      // debug(i, j, visited);
      rep(i2, H) rep(j2, W) chmax(ans, visited[i2][j2]);
    }

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