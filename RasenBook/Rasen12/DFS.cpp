// Rasen12.3 深さ優先探索
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 101
#define WHITE 0
#define GRAY 1
#define BLACK 2

int n, M[N][N];
int color[N], d[N], f[N], tt; // d[N]は開始時刻、f[N]は終了時刻, ttは時刻カウンタ

// 再帰関数による深さ優先探索
void dfs_visit(int u) {
  color[u] = GRAY;
  d[u] = ++tt; // GRAYにした時刻を記録してincr
  rep(v, n) {
    if (M[u][v] == 0) continue; // 隣接してない時は何もしない
    if (color[v] == WHITE) dfs_visit(v); // 隣接してて、未訪問なら訪問する
  }
  color[u] = BLACK; // 訪問が終わるのでBLACKに
  f[u] = ++tt; // BLACKにした時刻を記録してincr
}

void dfs() {
  // 初期化
  int u;
  rep(u, n) color[u] = WHITE;
  tt = 0;

  rep(u, n) {
    // 未訪問のuを始点として深さ優先探索
    if (color[u] == WHITE) dfs_visit(u);
  }

  // 出力
  rep(u, n) printf("%d %d %d\n", u+1, d[u], f[u]);
}

int main() {
  scanf("%d", &n);
  // 隣接行列の初期化
  rep(i, n) {
    rep(j, n) M[i][n] = 0;
  } 
  // 0 originにしながら、隣接リスト表現から隣接行列表現に変換
  rep(i, n) {
    int u, k, v;
    scanf("%d %d", &u, &k);
    u--;
    rep(j, k) {
      scanf("%d", &v);
      v--;
      M[u][v] = 1;
    }
  }

  dfs();

  return 0;
}