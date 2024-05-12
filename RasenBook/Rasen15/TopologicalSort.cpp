#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

// トポロジカルソートの昇順
vector<int> ans;
// 頂点iの入次数
vector<int> indeg(11000, 0);
// 頂点iの訪問状態の管理
vector<int> color(11000);
static const int WHITE = 0;
static const int BLACK = 2;
// 訪問する頂点
queue<int> myQueue;

void dfs(vector<vector<int> > &G, int w) {
  myQueue.push(w);
  color[w] = BLACK;

  while (!myQueue.empty()) {
    int s = myQueue.front();
    myQueue.pop();

    // 色の更新と入次数のデクリメントを行う
    for (int t : G[s]) {
      if (indeg[t] == 0) continue;
      indeg[t]--;
      if (indeg[t] == 0) {
        myQueue.push(t);
        color[t] = BLACK;
      }
    }
    ans.push_back(s);
  }
}

void topologicalSort(vector<vector<int> > &G, int v) {
  // 初期化処理
  rep(i, v) color[i] = WHITE;
  rep(i, v) {
    for (int u : G[i]) {
      indeg[u]++;
    }
  }

  // 未訪問で入次数が0のとこからdfs
  rep(i, v) {
    if (color[i] == WHITE && indeg[i] == 0) {
      // cout << "dfs開始：" << i << endl;
      dfs(G, i);
    }
  }
}

int main() {
  // 入力
  int v, e;
  cin >> v >> e;
  // 0-originの隣接リスト表現で表す
  vector<vector<int> > G(v);
  int s, t;
  rep(i, e) {
    cin >> s >> t;
    G[s].push_back(t);
  }
  // 幅優先探索でトポロジカルソートする
  topologicalSort(G, v);

  // 出力
  rep(i, v) cout << ans[i] << endl;

  return 0;
}