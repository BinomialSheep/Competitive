// Rasen12.2 グラフの表現
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


int main() {
  // 入力
  int n;
  cin >> n;
  vector<int> Adj[n];
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
  int ans[n][n];
  // 初期化
  rep(i, n) {
    rep(j, n) {
      ans[i][j] = 0;
    }
  }
  // 隣接リストに存在すれば1
  rep(i, n) { 
    vector<int> thisList = Adj[i];
    rep(j, thisList.size()) {
      ans[i][thisList[j]] = 1;
    }
  }
  
  // 出力
  rep(i, n) {
    rep(j, n) {
      cout << ans[i][j] << " ";
    }
    cout << endl;
  }


  return 0;
}