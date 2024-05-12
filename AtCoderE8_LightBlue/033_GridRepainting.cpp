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

void bfs(int H, int W, vvc &s, vvi &dist) {
  queue<pair<int, int>> q;
  //
  q.emplace(1, 1);
  dist[1][1] = 1;
  //
  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    vi dx = {-1, 0, 1, 0};
    vi dy = {0, 1, 0, -1};
    rep(i, 4) {
      int x = p.second + dx[i];
      int y = p.first + dy[i];
      if (s[y][x] == '.' && dist[y][x] == -1) {
        dist[y][x] = dist[p.first][p.second] + 1;
        q.emplace(y, x);
      }
    }
  }
}

int cnt(int H, int W, vvc &s) {
  int ret = 0;
  rep(i, H + 2) rep(j, W + 2) if (s[i][j] == '.') ret++;
  return ret;
}

int main() {
  /* input */
  int H, W;
  cin >> H >> W;
  vvc s(H + 2, vc(W + 2, '#'));
  rep(i, H) rep(j, W) cin >> s[i + 1][j + 1];
  /* solve */
  vvi dist(H + 2, vi(W + 2, -1));
  bfs(H, W, s, dist);
  //
  int len = dist[H][W];
  int num = cnt(H, W, s);

  /* output */
  cout << (len == -1 ? -1 : num - len) << endl;

  return 0;
}