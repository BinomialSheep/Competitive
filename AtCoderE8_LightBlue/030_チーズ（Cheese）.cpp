#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

void bfs(int sy, int sx, vvi &dist, vvc &maze) {
  queue<pair<int, int>> q;
  q.emplace(sy, sx);
  dist[sy][sx] = 0;
  vector<int> dy = {-1, 0, 1, 0};
  vector<int> dx = {0, 1, 0, -1};

  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    rep(i, 4) {
      int y = p.first + dy[i];
      int x = p.second + dx[i];
      // cout << p.first << " " << p.second << " " << y << " " << x << endl;
      if (maze[y][x] != 'X' && dist[y][x] == -1) {
        dist[y][x] = dist[p.first][p.second] + 1;
        q.emplace(y, x);
      }
    }
  }
}

int main() {
  /* input */
  int H, W, N;
  cin >> H >> W >> N;
  vvc maze(H + 2, vector<char>(W + 2, 'X'));
  for (int i = 1; i <= H; i++) {
    for (int j = 1; j <= W; j++) {
      cin >> maze[i][j];
    }
  }

  /* solve */
  vpii start(N + 1);
  rep(i, H + 2) rep(j, W + 2) {
    if ('1' <= maze[i][j] && maze[i][j] <= '9') {
      start[maze[i][j] - '0'] = make_pair(i, j);
    }
    if (maze[i][j] == 'S') start[0] = make_pair(i, j);
  }
  // rep(i, N + 1) cout << start[i].first << start[i].second << endl;
  //
  ll ans = 0;
  //
  rep(i, N) {
    // 距離のリセット
    vvi dist(H + 2, vector<int>(W + 2, -1));
    // 探索
    bfs(start[i].first, start[i].second, dist, maze);
    //
    ans += dist[start[i + 1].first][start[i + 1].second];
  }

  /* output */
  cout << ans << endl;

  return 0;
}