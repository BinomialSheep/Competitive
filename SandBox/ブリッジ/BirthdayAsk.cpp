#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

void print(int n, int v) {
  // 代
  cout << n / 5 + 1;
  // スーツ
  if (n % 5 == 0) cout << "C";
  if (n % 5 == 1) cout << "D";
  if (n % 5 == 2) cout << "H";
  if (n % 5 == 3) cout << "S";
  if (n % 5 == 4) cout << "NT";
  cout << ":" << v << endl;
}

int main() {
  /* input */

  /* 方針
  結局レスポンダーは366通り答えるので、オープンは1種類でいい
  オープナーは常に+1でaskするべき
  上からDPで求める
  例：
  7Hでaskすると、2通りのレスポンスが得られるので2種類
  7Cでaskすると、7Dが返ってきたら7HでReaskして2通り得られるので、2+(7H以降のレスポンス)=5種類
  */

  /* solve */
  // 1Cから7NTは35種類
  const int KIND = 35;
  const int N7 = 34;
  const int S7 = 33;

  vector<int> dp(KIND);
  // 初期値.
  dp[N7] = 1;
  // 漸化式部分
  for (int i = S7; i >= 0; i--) {
    // 7Sまでが返ってきた場合
    for (int j = i + 1; j <= S7; j++) {
      // jが返ってきたらj+1でaskする
      dp[i] += dp[j + 1];
    }
    // 7NTが返ってきた場合
    dp[i]++;
  }

  /* output */
  rep(i, KIND) print(i, dp[i]);

  return 0;
}