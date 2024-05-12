#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

static const ll INFTY = (1LL << 32);

void floyd(vector<vector<int>> &G, int n, vector<vector<int>> &used) {
  rep(k, n) rep(i, n) {
    if (G[i][k] == INFTY) {
      continue;
    }
    rep(j, n) {
      if (G[k][j] == INFTY) {
        // used[i][j] = 1;
        continue;
      }
      if (G[i][j] > G[i][k] + G[k][j]) {
        used[i][j] = -1;
        G[i][j] = G[i][k] + G[k][j];
      } else {
        // used[i][j] = 1;
      }
    }
    // G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  // G[A][B] == Cとなる
  vector<vector<int>> G(n, vector<int>(n));
  // 最短点間を求める時に使った辺は1, 使っていない辺は-1, どちらでもいい辺はgray
  vector<vector<int>> used(n, vector<int>(n, 1));
  int a, b, c;
  rep(i, m) {
    cin >> a >> b >> c;
    G[a - 1][b - 1] = G[b - 1][a - 1] = c;
    used[a - 1][b - 1] = used[b - 1][a - 1] = 1;
  }

  floyd(G, n, used);

  int count = 0;
  rep(i, n) {
    rep(j, n) {
      // if (G[i][j] != 0) {
      //   cout << "i, j, G[i][j], used[i][j] " << i << j << " " << G[i][j] << "
      //   "
      //        << used[i][j] << endl;
      // }
      // 減らしていい辺
      if (G[i][j] != 0 && used[i][j] == -1) {
        count++;
      }
    }
  }

  // 2回カウントしてるので1/2する
  cout << count / 2 << endl;

  return 0;
}