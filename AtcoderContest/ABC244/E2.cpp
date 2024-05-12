#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
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
  int n, m, k, s, t, x;
  cin >> n >> m >> k >> s >> t >> x;
  s--;
  t--;
  x--;
  vector<vector<int>> graph(n);
  rep(i, m) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  /* solve */
  int MOD = 998244353;
  // 頂点sから、辺をi回通って頂点jへ到達した時に、途中で頂点xを通った回数のmod2がhであるような方法の数をdp[i][j][h]とする
  vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(n, vector<int>(2)));
  // init
  rep(j, n) dp[0][j][0] = dp[0][j][1] = 0;
  dp[0][s][0] = 1;
  // recurrence
  rep(i, k) {
    rep(j, n) {
      rep(g, graph[j].size()) {
        rep(h, 2) {
          if (graph[j][g] == x) {
            dp[i + 1][graph[j][g]][(h + 1) % 2] += dp[i][j][h];
            dp[i + 1][graph[j][g]][(h + 1) % 2] %= MOD;
          } else {
            dp[i + 1][graph[j][g]][h] += dp[i][j][h];
            dp[i + 1][graph[j][g]][h] %= MOD;
          }
        }
      }
    }
    // rep(j, n) rep(h, 2) {
    //   cout << "dp" << i << j << h << ":" << dp[i][j][h] << " ";
    // }
    // cout << endl;
  }

  /* output */
  cout << dp[k][t][0] << endl;

  return 0;
}