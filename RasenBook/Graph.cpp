// Rasen12.2 グラフの表現
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
  // 入力
  int n;
  cin >> n;
  vector<vector<int>> Adj(n + 1);
  rep(i, n) {
    int u, k;
    cin >> u >> k;
    vector<int> vList(k);
    rep(j, k) {
      cin >> vList[j];
    }
    Adj[u] = vList;
  }
  // 隣接行列の作成
  int ans[n + 1][n + 1];
  // 初期化
  rep(i, n + 1) {
    rep(j, n + 1) {
      ans[i][j] = 0;
    }
  }
  // 隣接リストに存在すれば1
  rep(i, n) {
    vector<int> thisList = Adj[i + 1];
    rep(j, thisList.size()) {
      ans[i + 1][thisList[j]] = 1;
    }
  }
  
  // 出力
  rep(i, n) {
    rep(j, n - 1) {
      cout << ans[i + 1][j + 1] << " ";
    }
    cout << ans[i + 1][n] << endl;
  }

  return 0;
}