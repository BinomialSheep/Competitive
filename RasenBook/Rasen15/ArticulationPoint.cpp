#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define MAX 100000

vector<int> G[MAX];
int N;
bool visited[MAX];
int prenum[MAX], parent[MAX], lowest[MAX], timer;

void dfs(int current, int prev) {
  // ノード current を訪問した直後の処理
  // グローバルなtimerによって訪問順を管理している（vectorでよくない？）
  prenum[current] = lowest[current] = timer;
  timer++;

  visited[current] = true;

  int next;

  rep(i, G[current].size()) {
    next = G[current][i];
    if (!visited[next]) {
      // ノードcurrentからノードnextへ訪問する直前の処理
      parent[next] = current;
      dfs(next, current);
      // ノードnextの探索が終了した直後の処理
      lowest[current] = min(lowest[current], lowest[next]);
    } else if (next != prev) {
      // 訪問済みかつ直前以外（つまりBack-edge）の場合の処理
      lowest[current] = min(lowest[current], prenum[next]);
    }
  }
  // ノード currentの探索が終了した直後の処理
}

// Articulation Points（関節点）
void art_points() {
  // 初期化
  rep(i, N) visited[i] = false;
  timer = 1;

  // lowestの計算
  dfs(0, -1);  // 0 == root

  // 関節点判定をする
  set<int> artPointSet;
  // rootの子どもの判定
  int rootChildlen = 0;
  // i = 0(root)の場合は別処理なのでi=0を除外
  for (int i = 1; i < N; i++) {
    int p = parent[i];
    if (p == 0) {
      rootChildlen++;
    } else if (prenum[p] <= lowest[i]) {
      // 子孫から祖先への経路がないなら関節点（各頂点の親が関節点か判定している）
      artPointSet.insert(p);
    }
  }
  // i=0(root)の場合は、子が2以上なら関節点
  if (rootChildlen > 1) artPointSet.insert(0);
  for (set<int>::iterator it = artPointSet.begin(); it != artPointSet.end();
       it++) {
    cout << *it << endl;
  }
}

int main() {
  int m;
  cin >> N >> m;

  rep(i, m) {
    int s, t;
    cin >> s >> t;
    G[s].push_back(t);
    G[t].push_back(s);
  }
  art_points();

  return 0;
}