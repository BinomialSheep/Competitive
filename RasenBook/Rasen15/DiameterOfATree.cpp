#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define MAX 100000
#define INFTY (1 << 30)

class Edge {
 public:
  int t, w;
  Edge() {}
  Edge(int t, int w) : t(t), w(w) {}
};

vector<Edge> G[MAX];
int n, d[MAX];
bool vis[MAX];
int cnt;

void bfs(int s) {
  rep(i, n) d[i] = INFTY;
  queue<int> Q;
  Q.push(s);
  d[s] = 0;

  int u;
  while (!Q.empty()) {
    u = Q.front();
    Q.pop();
    rep(i, G[u].size()) {
      Edge e = G[u][i];
      if (d[e.t] == INFTY) {
        d[e.t] = d[u] + e.w;
        Q.push(e.t);
      }
    }
  }
}

void solve() {
  // 適当な点から最も遠い節点tgtを求める
  bfs(0);
  int maxv = 0;
  int tgt = 0;
  rep(i, n) {
    if (d[i] == INFTY) continue;
    if (maxv < d[i]) {
      maxv = d[i];
      tgt = i;
    }
  }
  // tgtから最も遠い節点の距離maxvを求める
  bfs(tgt);
  maxv = 0;
  rep(i, n) {
    if (d[i] == INFTY) continue;
    maxv = max(maxv, d[i]);
  }

  cout << maxv << endl;
}

int main() {
  int s, t, w;
  cin >> n;

  rep(i, n - 1) {
    cin >> s >> t >> w;
    G[s].push_back(Edge(t, w));
    G[t].push_back(Edge(s, w));
  }

  solve();

  return 0;
}