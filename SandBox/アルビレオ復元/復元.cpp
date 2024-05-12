#include <bits/stdc++.h>
// デバッグ用マクロ：https://naskya.net/post/0002/
#ifdef LOCAL
#include <debug_print.hpp>
#define debug(...) debug_print::multi_print(#__VA_ARGS__, __VA_ARGS__)
#else
#define debug(...) (static_cast<void>(0))
#endif
using namespace std;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vector G(N, vector<int>());
  vector<pair<int, int>> Edges;
  rep(i, M) {
    int A, B;
    cin >> A >> B;
    Edges.emplace_back(A, B);
    --A, --B;
    G[A].push_back(B);
    G[B].push_back(A);
  }
  vector<int> visitable(N);
  rep(i, N) cin >> visitable[i];

  /* solve */
  vector<int> visited(N);       // 頂点の訪問回数
  map<pair<int, int>, int> mp;  // 辺を通った回数
  vector<int> path;             // 復元用

  auto dfs = [&](auto rec, int v) -> bool {
    bool ret = false;
    visited[v]++;
    path.push_back(v);
    // 全ての辺を通っていればOK
    if ((int)mp.size() == M) return true;
    // 1:全ての辺を見る 2:未到達辺のみ見る 3: 葉への辺だけ見る
    int type = 1;
    // typeの決定と、枝狩り
    for (auto u : G[v]) {
      pair<int, int> p = make_pair(min(v, u), max(v, u));
      if (mp.count(p) == 0) {
        // 使用不可の辺ができていたら絶対false
        if (visited[u] == visitable[u]) return false;
        // 未到達辺があればそれを使う
        type = 2;
      }
    }

    // 実際にDFS
    for (auto u : G[v]) {
      if (visited[u] == visitable[u]) continue;
      pair<int, int> p = make_pair(min(v, u), max(v, u));
      // 枝狩り
      if (type == 2 && mp.count(p)) continue;
      mp[p]++;
      if (rec(rec, u)) ret = true;
      if (ret) break;
      if (--mp[p] == 0) mp.erase(p);
    }
    if (!ret) visited[v]--, path.pop_back();
    return ret;
  };

  // 全始点DFS
  int hasDeg1 = 0;
  rep(i, N) if (G[i].size() == 1) hasDeg1++;
  int ok = 0;
  rep(i, N) {
    debug(i);
    if (hasDeg1 && G[i].size() > 1) continue;  // 枝狩り
    path.clear();
    ok = dfs(dfs, i);
    if (ok) break;
  }

  /* output */
  if (ok) {
    printf("%d %d\n", N, M);
    for (auto [a, b] : Edges) printf("%d %d\n", a, b);
    for (auto v : visited) cout << v << " ";
    cout << "\n";
    for (auto v : path) cout << v << " ";
    cout << endl;
  } else {
    cout << -1 << endl;
  }
}