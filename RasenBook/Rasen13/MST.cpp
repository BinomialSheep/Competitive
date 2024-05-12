#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;

static const int MAX = 100;
static const int INFTY = (1 << 21);
static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;

int n, M[MAX][MAX];

int prim() {
  int u, minv;
  // d[v]に、Tに属する頂点とV-Tに属する頂点をつなぐ辺の中で、重みが最小の辺の重みを記録
  int d[MAX], parent[MAX], color[MAX];

  // 初期化
  rep(i, n) {
    d[i] = INFTY;
    parent[i] = -1;
    color[i] = WHITE;
  }

  // 始点
  d[0] = 0;

  while (true) {
    minv = INFTY;
    u = -1;
    // 次にMSTに繋ぐ頂点uを決める
    rep(i, n) {
      // まだMSTに繋いでいない辺の中で、重みが最小の頂点をuとする
      if (minv > d[i] && color[i] != BLACK) {
        u = i;
        minv = d[i];
      }
    }
    // もうMSTに繋ぐ頂点がなければbreak
    if (u == -1) break;
    // MSTに繋いだら色を変更
    color[u] = BLACK;
    rep(v, n) {
      // MSTに繋がっておらず、uと繋がってる頂点について、d[v]を更新
      // つまり、MSTに新しい辺が加わるごとにd[v]が更新されるというのがこのアルゴリズムの肝
      if (color[v] != BLACK && M[u][v] != INFTY) {
        if (d[v] > M[u][v]) {
          d[v] = M[u][v];
          parent[v] = u;
          color[v] = GRAY;
        }
      }
    }
  }

  // 返り値の計算
  int sum = 0;
  rep(i, n) {
    if (parent[i] != -1) sum += M[i][parent[i]];
  }
  return sum;
}

int main() {
  cin >> n;

  rep(i, n) {
    rep(j, n) {
      int e;
      cin >> e;
      M[i][j] = (e == -1) ? INFTY : e;
    }
  }

  cout << prim() << endl;

  return 0;
}