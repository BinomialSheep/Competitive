#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  // すべて0 indexed
  // スイッチiで付く電球のリスト（問題文とは逆引き）
  vector<vector<int>> sk(N);
  rep(i, M) {
    int k;
    cin >> k;
    rep(j, k) {
      int s;
      cin >> s;
      sk[s - 1].push_back(i);
    }
  }
  vector<int> p(M);
  rep(i, M) cin >> p[i];

  // debug
  // rep(i, N) {
  //   cout << "スイッチ" << i + 1 << ":";
  //   rep(j, sk[i].size()) { cout << sk[i][j] + 1 << " "; }
  //   cout << endl;
  // }

  /* solve */
  int ans = 0;
  vector<int> pCnt(M, 0);
  rep(bit, 1 << N) {
    //
    rep(i, N) {
      if (bit & (1 << i)) {
        // cout << "i桁目on" << bit << " " << i << endl;
        rep(j, sk[i].size()) { pCnt[sk[i][j]]++; }
      }
    }
    // 電球がすべてONかチェック
    bool flag = true;
    rep(i, pCnt.size()) {
      // cout << "電球" << i + 1 << ": スイッチ:" << pCnt[i] << endl;
      if (pCnt[i] % 2 != p[i]) {
        flag = false;
        break;
      }
    }
    if (flag) ans++;
    // 電球リセット
    rep(i, pCnt.size()) pCnt[i] = 0;
  }

  /* output */
  cout << ans << endl;

  return 0;
}