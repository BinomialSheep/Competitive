#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef long long ll;

static const int MAX = 100000;
static const int NIL = -1;

int n;
vector<int> G[MAX];
int color[MAX];

void dfs(int r, int c) {
  stack<int> S;
  S.push(r);
  color[r] = c;

  while ( !S.empty() ) {
    int u = S.top(); S.pop();
    rep(i, G[u].size()) {
      int v = G[u][i];
      // 未訪問なら色を付けて訪問済みとし、stackに加える
      if (color[v] == NIL) {
        color[v] = c;
        S.push(v);
      }
    }
  }
}

void assignColor() {
  int id = 1;
  rep(i, n) color[i] = NIL;
  rep(u, n) {
    // 色が付いていなければ付ける。idをincrしてるので色はユニークになる
    if(color[u] == NIL) dfs(u, id++);
  }
}


int main() {
  // 入力
  int m;
  cin >> n >> m;
  rep(i, m) {
    int s, t;
    cin >> s >> t;
    G[s].push_back(t);
    G[t].push_back(s);
  }

  assignColor();

  // 質問
  int q;
  cin >> q;
  rep(i, q) {
    int s, t;
    cin >> s >> t;
    if (color[s] == color[t]) cout << "yes" << endl;
    else cout << "no" << endl;
  }

  return 0;
}