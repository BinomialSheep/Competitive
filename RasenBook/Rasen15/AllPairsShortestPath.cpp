#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

static const int MAX = 100;
static const ll INFTY = (1LL << 32);
int n;
ll d[MAX][MAX];

void floyd() {
  rep(k, n) rep(i, n) {
    if (d[i][k] == INFTY) continue;
    rep(j, n) {
      if (d[k][j] == INFTY) continue;
      d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      // cout << d[i][j] << " ";
    }
  }
  // cout << endl;
}

int main() {
  int e, u, v, c;
  cin >> n >> e;

  // 初期化
  rep(i, n) rep(j, n) d[i][j] = ((i == j) ? 0 : INFTY);
  // 隣接行列表現で有向重み付きグラフを表す
  rep(i, e) {
    cin >> u >> v >> c;
    d[u][v] = c;
  }

  // rep(i, n) rep(j, n) cout << d[i][j] << " ";

  // 実行
  floyd();

  // 閉路判定
  bool negative = false;
  rep(i, n) if (d[i][i] < 0) negative = true;

  if (negative) {
    // 閉路がある場合
    cout << "NEGATIVE CYCLE" << endl;
  } else {
    // 閉路がない場合
    rep(i, n) {
      rep(j, n) {
        if (j) cout << " ";
        if (d[i][j] == INFTY)
          cout << "INF";
        else
          cout << d[i][j];
      }
      cout << endl;
    }
  }

  return 0;
}