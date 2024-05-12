#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;

using P = pair<int, int>;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> h(n);
  rep(i, n) cin >> h[i];
  vector<vector<int>> to(n);
  rep(i, m) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    to[a].push_back(b);
    to[b].push_back(a);
  }

  priority_queue<P, vector<P>, greater<P>> q;
  const int INF = 1001001001;
  vector<int> dist(n, INF);
  dist[0] = 0;
  q.emplace(0, 0);
  while (!q.empty()) {
    auto [d, v] = q.top();
    q.pop();
    if (dist[v] != d) continue;
    for (int u : to[v]) {
      int cost = max(0, h[u] - h[v]);
      int nd = d + cost;
      if (nd >= dist[u]) continue;
      dist[u] = nd;
      q.emplace(nd, u);
    }
  }

  int ans = 0;
  rep(i, n) {
    int now = h[0] - h[i] - dist[i];
    ans = max(ans, now);
  }
  cout << ans << endl;

  return 0;
}