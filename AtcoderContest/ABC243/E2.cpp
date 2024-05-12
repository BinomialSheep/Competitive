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

static const int INFTY = (1 << 30);

void floyd(vector<vector<int>> &G, int n) {
  rep(k, n) rep(i, n) {
    if (G[i][k] == INFTY) continue;
    rep(j, n) {
      if (G[k][j] == INFTY) continue;
      G[i][j] = min(G[i][j], G[i][k] + G[k][j]);
    }
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  // G[A][B] == Cとなる
  vector<vector<int>> G(n, vector<int>(n, INFTY));
  int a, b, c;
  rep(i, m) {
    cin >> a >> b >> c;
    G[a - 1][b - 1] = G[b - 1][a - 1] = c;
  }

  // あとで比較する退避用
  vector<vector<int>> copy(n, vector<int>(n));
  rep(i, n) rep(j, n) copy[i][j] = G[i][j];

  floyd(G, n);

  int count = 0;
  rep(a, n) {
    rep(b, n) {
      // 直接の辺がないなら無視
      if (copy[a][b] == INFTY) continue;

      // 最短距離にcopy[a][b]を使ってないなら削除する
      if (copy[a][b] > G[a][b]) {
        count++;
        continue;
      }
      rep(i, n) {
        if (a == i || b == i) {
          continue;
        }
        // 回り道しても距離が同じなら直接の辺は削除した方がいい
        if (copy[a][b] == G[a][i] + G[i][b]) {
          count++;
          break;
        }
      }
    }
  }

  // 2回カウントしてるので1/2する
  cout << count / 2 << endl;

  return 0;
}