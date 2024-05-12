#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
using namespace atcoder;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int n, m;
  cin >> n >> m;
  scc_graph g(n);
  vector<vector<int>> to(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    // gに辺を追加
    g.add_edge(a, b);
    to[a].push_back(b);
  }
  /* solve */
  vector<vector<int>> d = g.scc();
  int s = d.size();
  // 頂点から集合を逆算できるように
  vector<int> di(n);
  rep(i, s) for (int v : d[i]) di[v] = i;
  // トポロジカル逆順でdpする
  vector<bool> dp(s);
  for (int i = s - 1; i >= 0; i--) {
    // その集合自身がサイクルかどうかで初期化
    dp[i] = d[i].size() != 1;
    for (int v : d[i]) {
      for (int u : to[v]) {
        // 各集合の各頂点を舐めてる
        // サイクルに到達できるならtrue
        if (dp[di[u]]) dp[i] = true;
      }
    }
  }

  /* output */
  int ans = 0;
  rep(i, s) if (dp[i]) ans += d[i].size();
  cout << ans << endl;
  return 0;
}