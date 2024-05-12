#include <bits/stdc++.h>
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
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

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
    vs maze;
    cin >> H >> W;
    maze.resize(H);

    rep(i, H) cin >> maze[i];

    /* solve */
    // dp[y][x]
    vvi dp(H, vi(W, INFTY));

    if (maze[0][0] == '#')
      dp[0][0] = 1;
    else
      dp[0][0] = 0;

    queue<pii> q;
    q.emplace(0, 0);
    while (!q.empty()) {
      auto p = q.front();
      q.pop();
      int y = p.first;
      int x = p.second;

      if (y != H - 1) {
        if (maze[y][x] == '.' && maze[y + 1][x] == '#') {
          if (chmin(dp[y + 1][x], dp[y][x] + 1)) {
            q.emplace(y + 1, x);
          }
        } else {
          if (chmin(dp[y + 1][x], dp[y][x])) {
            q.emplace(y + 1, x);
          }
        }
      }
      if (x != W - 1) {
        if (maze[y][x] == '.' && maze[y][x + 1] == '#') {
          if (chmin(dp[y][x + 1], dp[y][x] + 1)) {
            q.emplace(y, x + 1);
          }
        } else {
          if (chmin(dp[y][x + 1], dp[y][x])) {
            q.emplace(y, x + 1);
          }
        }
      }
    }

    string tmp = {maze[0][0]};

    /* output */
    cout << dp[H - 1][W - 1] << endl;
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