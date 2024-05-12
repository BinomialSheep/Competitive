#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;

static const int N = 100;
static const int INFTY = (1<<21);

int n, M[N][N];
int d[N]; // 距離. 未訪問の場合はINFTY

void bfs(int s) {
  queue<int> q;
  q.push(s);
  rep(i, n) d[i] = INFTY;
  d[s] = 0;
  int u;
  while (!q.empty()) {
    u = q.front(); q.pop();
    rep(v, n) {
      if (M[u][v] == 0) continue;
      if (d[v] != INFTY) continue;
      d[v] = d[u] + 1;
      q.push(v);
    }
  }
  rep(i, n) {
    cout << i+1 << " " << ( (d[i] == INFTY) ? -1 : d[i] ) << endl;
  }
}


int main() {
  cin >> n;
  // 初期化
  rep(i, n) {
    rep(j, n) M[i][j] = 0;
  }
  // 隣接行列表現に変換
  rep(i, n) {
    int u, k;
    cin >> u >> k;
    u--;
    rep(j, k) {
      int v;
      cin >> v;
      v--;
      M[u][v] = 1;

    }
  }

  bfs(0);

  return 0;
}