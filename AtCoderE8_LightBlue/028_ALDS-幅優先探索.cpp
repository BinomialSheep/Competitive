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

void bfs(vector<vector<int>> &G, vector<int> &dist, int n) {
  queue<int> q;
  q.push(0);
  dist[0] = 0;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : G[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }
}

int main() {
  /* input */
  int n;
  cin >> n;
  vector<vector<int>> G(n);
  rep(i, n) {
    int u, k;
    cin >> u >> k;
    --u;
    G[u].resize(k);
    rep(j, k) {
      int v;
      cin >> v;
      --v;
      G[u][j] = v;
    }
  }
  vector<int> dist(n, -1);
  /* solve */
  bfs(G, dist, n);

  /* output */
  rep(i, n) cout << i + 1 << " " << dist[i] << endl;

  return 0;
}