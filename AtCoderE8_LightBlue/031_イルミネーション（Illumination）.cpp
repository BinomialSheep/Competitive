#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int W, H;

void bfs(int sy, int sx, vvi &maze, vvi &color) {
  queue<pair<int, int>> q;
  q.emplace(sy, sx);
  color[sy][sx] = 1;
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    vi dy = {-1, -1, 0, 0, 1, 1};
    vi dxE = {-1, 0, -1, 1, -1, 0};
    vi dxO = {0, 1, -1, 1, 0, 1};
    rep(i, 6) {
      int y = p.first + dy[i];
      int x = p.second + (p.first % 2 == 1 ? dxO[i] : dxE[i]);
      if (x < 0 || y < 0 || W + 1 < x || H + 1 < y) continue;
      if (maze[y][x] == 0 && color[y][x] == 0) {
        q.emplace(y, x);
        color[y][x] = 1;
      }
    }
  }
}

int cnt(vvi &maze, vvi &color) {
  vi dy = {-1, -1, 0, 0, 1, 1};
  vi dxE = {-1, 0, -1, 1, -1, 0};
  vi dxO = {0, 1, -1, 1, 0, 1};
  int ret = 0;

  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      // cout << ret << " ";
      if (maze[i][j] == 0) continue;
      rep(k, 6) {
        int y = i + dy[k];
        int x = (i % 2 == 1 ? j + dxO[k] : j + dxE[k]);
        if (color[y][x] == 1) ret++;
      }
    }
    // cout << endl;
  }
  return ret;
}

int main() {
  /* input */
  cin >> W >> H;
  vvi maze(H + 2, vector<int>(W + 2));
  rep(i, H) rep(j, W) cin >> maze[i + 1][j + 1];
  /* solve */
  vvi color(H + 2, vi(W + 2));
  // 外側を色塗りする
  rep(i, H) {
    if (color[i][0] == 0) bfs(i, 0, maze, color);
    if (color[i][W + 1] == 0) bfs(i, W + 1, maze, color);
  }
  rep(j, W) {
    if (color[0][j] == 0) bfs(0, j, maze, color);
    if (color[H + 1][j] == 0) bfs(H + 1, j, maze, color);
  }
  // rep(i, H + 2) {
  //   rep(j, W + 2) { cout << color[i][j]; }
  //   cout << endl;
  // }

  int ans = cnt(maze, color);

  /* output */
  cout << ans << endl;

  return 0;
}