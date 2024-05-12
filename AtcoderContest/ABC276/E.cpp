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
    vs C(H);
    rep(i, H) cin >> C[i];

    /* solve */
    int startX, startY;
    rep(i, H) rep(j, W) if (C[i][j] == 'S') {
      startY = i;
      startX = j;
      break;
    }

    vpii startEnd;
    vi dy = {-1, 1, 0, 0};
    vi dx = {0, 0, -1, 1};
    rep(i, 4) {
      int y = startY + dy[i];
      int x = startX + dx[i];
      if (0 <= y && y < H && 0 <= x && x < W) {
        if (C[y][x] == '.') startEnd.emplace_back(y, x);
      }
    }
    if (startEnd.size() <= 1) {
      cout << "No" << endl;
      return;
    }
    rep(si, startEnd.size()) rep(sj, si) {
      auto start = startEnd[si];
      auto end = startEnd[sj];
      // debug(start, end);

      vvi used(H, vi(W));
      queue<pair<int, int>> q;
      q.push(start);
      used[start.first][start.second] = 1;
      while (!q.empty()) {
        auto p = q.front();
        // debug(p);
        if (p == end) {
          cout << "Yes" << endl;
          return;
        }
        q.pop();
        rep(i, 4) {
          int y = p.first + dy[i];
          int x = p.second + dx[i];
          if (0 <= y && y < H && 0 <= x && x < W) {
            if (C[y][x] == '.' && used[y][x] == 0) {
              q.emplace(y, x);
              used[y][x] = 1;
            }
          }
        }
      }
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