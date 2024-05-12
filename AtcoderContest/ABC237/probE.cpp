#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;


static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;

static const int MINUS_INFTY = - (1<<21);




int main() {
  int n, m;
  cin >> n >> m;
  int H[n];
  rep(i, n) cin >> H[i];


  // 隣接リスト
  vector<int> G[n];
  int u, v;
  rep(i, m){
    cin >> u >> v;
    u--; // convert 0-origin
    v--;
    G[u].push_back(v);
    G[v].push_back(u);
  }

  // 楽しさ
  int d[n];
  rep(i, n) d[i] = MINUS_INFTY;
  d[0] = 0;

  // 幅優先探索で各広場で終えた時の最大の楽しさを計算
  queue<int> q;
  q.push(0);
  int x;
  while( !q.empty() ) {
    x = q.front(); q.pop();
    vector<int> xList = G[x]; 
    int l = xList.size();
    rep(i, l) {
      int y = xList[i];
      if(d[y] == MINUS_INFTY) q.push(y);
      // 楽しさ差分の計算
      int diff = 0;
      if(H[x] > H[y]) diff = H[x] - H[y];
      else if (H[x] < H[y]) diff = -2 * (H[y] - H[x]);
      // 楽しさ値の更新
      d[y] = max(d[y], d[x] + diff);
    }
  }
  
  // 出力
  int ans = 0;
  rep(i, n) ans = max(ans, d[i]);
  cout << ans << endl;
  
  return 0;
  
}