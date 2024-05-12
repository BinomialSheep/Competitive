#include <bits/stdc++.h>

using namespace std;

typedef long long ll;



vector<vector<pair<int, int>>> allComb;

void rec(vector<int> rem, vector<pair<int, int>> pairVec) {
  // 残りが0人なら終わり
  if(rem.empty()){
    allComb.push_back(pairVec);
    return;
  }

  // 残ってる人から選ぶ2人を決める
  // 最初に選ぶペアの1人目をvectorの先頭に固定しても一般性は失われない
  int fst = rem[0];
  for(int i = 1; i < rem.size(); i++) {
    // 選んだ2人をペアとして追加
    pair<int, int> p(fst, rem[i]);
    pairVec.push_back(p);
    // 選んだ2人をremから除外したリストを作る
    vector<int> newRem;
    for(int k = 1; k < rem.size(); k++) if(k != i) newRem.push_back(rem[k]);
    // 次のペアを再帰的に生成
    rec(newRem, pairVec);
    // HACK：これだと次のループにpairVecが持ち越されるので仕方なく消す
    pairVec.pop_back();
  }

}




void makeComb(int n) {
  // 余りの人
  vector<int> rem;
  for(int i = 1; i <= 2 * n; i++) rem.push_back(i);

  // ありうる組み合わせのうちの1つ
  vector<pair<int, int>> pairVec;

  rec(rem, pairVec);

}


int main() {
  int n;
  cin >> n;

  int a[2 * n + 1][2 * n + 1];
  for (int i = 1; i <= 2 * n - 1; i++) {
    for (int j = i + 1; j <= 2 * n; j++) {
      cin >> a[i][j];

    }
  }



  makeComb(n);

  int fanScore;
  vector<int> fanScoreVec;

  for(vector<pair<int, int>> pairVec : allComb) {
    fanScore = 0;
    // 排他的論理和を計算
    for (pair<int, int> p : pairVec) {
      // cout << "fst:" << p.first << " scn:" << p.second <<" v:" << a[p.first][p.second] << endl;
      fanScore ^= a[p.first][p.second];
    }
    fanScoreVec.push_back(fanScore);
  }

/*
    for(vector<pair<int, int>> pairVec : allComb) {
      cout << "pairVec: " << endl;
    for (pair<int, int> p : pairVec) {
      cout << "{" << p.first << ", " << p.second << "} ";
    }
    cout << endl;
  }
  */

  int ans = 0;
  for(int score : fanScoreVec ) {
    if(ans < score) ans = score;
  }


  cout << ans << endl;



  return 0;
}