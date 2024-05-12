#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int R, C, sy, sx, gy, gx;
  cin >> R >> C >> sy >> sx >> gy >> gx;
  --sy;
  --sx;
  --gy;
  --gx;
  vector<vector<char>> maze(R, vector<char>(C));
  rep(i, R) rep(j, C) cin >> maze[i][j];

  /* solve */
  vector<vector<int>> dist(R, vector<int>(C, -1));
  dist[sy][sx] = 0;
  queue<pair<int, int>> q;
  q.emplace(sy, sx);
  vector<int> vertical = {0, 1, 0, -1};
  vector<int> lateral = {-1, 0, 1, 0};
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    rep(i, 4) {
      int y = p.first + vertical[i];
      int x = p.second + lateral[i];
      if (maze[y][x] == '.' && dist[y][x] == -1) {
        dist[y][x] = dist[p.first][p.second] + 1;
        //cout << "y, x, dist:" << y << " " << x << " " << dist[y][x] << endl;
        q.emplace(y, x);
      }
    }
  }

  /* output */
  cout << dist[gy][gx] << endl;

  return 0;
}