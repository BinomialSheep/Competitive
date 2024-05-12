#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;

static const int MAX = 10000;
static const int INFTY = (1 << 21);
static const int WHITE = 0;
static const int GRAY = 1;
static const int BLACK = 2;

int n;
vector<pair<int, int> > adj[MAX];  // 重み付き有向グラフの隣接リスト表現

void dijkstra() {
  priority_queue<pair<int, int> > PQ;
  int color[MAX];
  int d[MAX];
  rep(i, n) {
    d[i] = INFTY;
    color[i] = WHITE;
  }

  d[0] = 0;
  PQ.push(make_pair(0, 0));
  color[0] = GRAY;

  while (!PQ.empty()) {
    pair<int, int> f = PQ.top();
    PQ.pop();
    int u = f.second;
    color[u] = BLACK;
    // 最小値を取り出し、それが最短でなければ無視
    if (d[u] < f.first * (-1)) continue;
    // この時点でfは、（現在木を形成していない頂点の中で）rootからの最短の頂点とその距離のペアとなる

    // uと接する頂点までの最短を更新していく
    rep(j, adj[u].size()) {
      int v = adj[u][j].first;
      if (color[v] == BLACK) continue;
      if (d[v] > d[u] + adj[u][j].second) {
        d[v] = d[u] + adj[u][j].second;
        // PQはデフォルトで大きい値を優先するため、-1を掛ける
        PQ.push(make_pair(d[v] * (-1), v));
        color[v] = GRAY;
      }
    }
  }

  // 出力
  rep(i, n) cout << i << " " << (d[i] == INFTY ? -1 : d[i]) << endl;
}

int main() {
  cin >> n;

  int k, c, u, v;
  rep(i, n) {
    cin >> u >> k;
    rep(j, k) {
      cin >> v >> c;
      // cは頂点番号、vは重み
      adj[u].push_back(make_pair(v, c));
    }
  }

  dijkstra();

  return 0;
}