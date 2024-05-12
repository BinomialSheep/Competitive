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

int w, h;

void bfs(vvi &hw, vvi &ww, vvi &dist) {
  queue<pair<int, int>> q;
  q.emplace(0, 0);
  dist[0][0] = 1;

  while (!q.empty()) {
    auto p = q.front();
    q.pop();
    // 上
    if (p.first != 0 && dist[p.first - 1][p.second] == -1) {
      if (ww[p.first - 1][p.second] == 0) {
        dist[p.first - 1][p.second] = dist[p.first][p.second] + 1;
        q.emplace(p.first - 1, p.second);
      }
    }
    // 下
    if (p.first != h - 1 && dist[p.first + 1][p.second] == -1) {
      if (ww[p.first][p.second] == 0) {
        dist[p.first + 1][p.second] = dist[p.first][p.second] + 1;
        q.emplace(p.first + 1, p.second);
      }
    }
    // 左
    if (p.second != 0 && dist[p.first][p.second - 1] == -1) {
      if (hw[p.first][p.second - 1] == 0) {
        dist[p.first][p.second - 1] = dist[p.first][p.second] + 1;
        q.emplace(p.first, p.second - 1);
      }
    }
    // 右
    if (p.second != w - 1 && dist[p.first][p.second + 1] == -1) {
      if (hw[p.first][p.second] == 0) {
        dist[p.first][p.second + 1] = dist[p.first][p.second] + 1;
        q.emplace(p.first, p.second + 1);
      }
    }
  }
}

void printDist(vvi &dist) {
  rep(i, h) {
    rep(j, w) { cout << max(dist[i][j], 0); }
    cout << endl;
  }
}

int main() {
  while (true) {
    /* input */
    cin >> w >> h;
    if (w == 0 && h == 0) break;
    // 縦方向の壁(hw[i][j]は、(i, j)の右の壁)
    vvi hw(h, vi(w - 1));
    // 横方向の壁(ww[i][j]は(i, j)の下の壁)
    vvi ww(h - 1, vi(w));
    rep(i, 2 * h - 1) {
      if (i % 2 == 0) {
        rep(j, w - 1) cin >> hw[i / 2][j];
      } else {
        rep(j, w) cin >> ww[i / 2][j];
      }
    }

    /* solve */
    vvi dist(h, vi(w, -1));
    bfs(hw, ww, dist);

    /* output */
    // printDist(dist);
    cout << max(dist[h - 1][w - 1], 0) << endl;
  }

  return 0;
}