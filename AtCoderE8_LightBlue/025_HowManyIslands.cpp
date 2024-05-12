#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

vector<vector<int>> c;
// -1は未探索、0は探索中、1は探索少量
vector<vector<int>> color;

int width;
int height;

void initColor(int w, int h) {
  color.resize(h);
  rep(i, h) rep(j, w) color[i].push_back(-1);
}

void dfs(int h, int w) {
  color[h][w] = 0;
  // 周り8マスを調べる
  vector<int> col = {-1, 0, 1};
  vector<int> row = {-1, 0, 1};
  rep(i, 3) rep(j, 3) {
    int h2 = h + col[i];
    int w2 = w + row[j];
    if (h2 < 0 || height <= h2 || w2 < 0 || width <= w2) continue;
    if (c[h2][w2] == 0) continue;
    if (color[h2][w2] != -1) continue;
    dfs(h2, w2);
  }
  color[h][w] = 1;
}

int main() {
  while (true) {
    /* input */
    int w, h;
    cin >> w >> h;
    if (w == 0 && h == 0) break;
    c.resize(h);
    rep(i, h) rep(j, w) {
      int a;
      cin >> a;
      c[i].push_back(a);
    }

    width = w;
    height = h;

    /* solve */
    initColor(w, h);
    int ans = 0;
    rep(i, h) rep(j, w) {
      if (c[i][j] == 1 && color[i][j] == -1) {
        ans++;
        dfs(i, j);
      }
    }

    /* output */
    cout << ans << endl;
    // クリア
    c.clear();
    color.clear();
  }

  return 0;
}