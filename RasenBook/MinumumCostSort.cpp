#include <bits/stdc++.h>

using namespace std;

typedef long long ll;


static const int MAX = 1000;
static const int VMAX = 10000;

int n, A[MAX], small;
int B[MAX], T[VMAX+1];

int solve() {
  int ans = 0;
  bool V[MAX]; // 探索済みフラグの配列

  // B[]にA[]をコピーし、V[]を初期化
  for (int i = 0; i < n; i++ ) {
    B[i] = A[i];
    V[i] = false;
  }
  // B[]は昇順にソート
  sort(B, B + n);

  // 値を入れるとソート後のindexが帰ってくる関数として使用
  for( int i = 0; i < n; i++ ) T[B[i]] = i;
  
  // 移動後のindexのサイクルを考えていく（0 → 3 → 5 → 0, 1 → 1, 2 → 4 → 2のように）
  for( int i = 0; i < n; i++ ) {
    if(V[i]) continue; // 以前までのサイクルに出てきた要素はもう計算済み
    int cur = i; // 今調べてるindex
    int S = 0; // サイクル内の要素の値の総和
    int m = VMAX; // このサイクルの最小値
    int an = 0; // サイクル内の要素の個数

    while(true) {
      V[cur] = true; // 訪問済みとする
      an++;
      int v = A[cur];
      m = min(m, v);
      S += v;
      cur = T[v]; // 次に訪問するindex
      if(V[cur]) break; // サイクルができたら終わり
    }
    // 1引数目は「そのサイクル内で上手く交換した時のコスト（サイクルの最小値を働かせる）」
    // 2引数目は「サイクルの外から配列最小値を借りてきて上手く交換した時のコスト（最初と最後に借りて返すコストが余分に掛かるが、道中のコストが安く済む）」
    ans += min(S + (an - 2) * m, m + S + (an + 1) * small);
  }

  return ans;
}




int main() {
  cin >> n;
  small = VMAX;
  for(int i = 0; i < n; i++){
    cin >> A[i];
    small = min(small, A[i]);
  }

  int ans = solve();
  
  cout << ans << endl;
  return 0;
}