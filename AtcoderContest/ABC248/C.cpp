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

int main() {
  /* input */
  int N, M, K;
  cin >> N >> M >> K;
  ll MOD = 998244353;

  /* solve */
  // 今の桁数, 今のsum
  vector<vector<ll>> dp(N, vector<ll>(K + 1, 0));
  // 最初の桁
  for (int j = 1; j <= M; j++) {
    dp[0][j] = 1;
  }
  // A_iまで足して、
  for (int i = 1; i < N; i++) {
    // A_iが1からMの時、
    for (int j = 1; j <= M; j++) {
      for (ll k = 1; k + j <= K; k++) {
        //
        dp[i][k + j] += dp[i - 1][k];
        dp[i][k + j] = dp[i][k + j] % MOD;
      }
    }
  }

  /* output */
  //
  ll ans = 0;
  rep(i, K + 1) {
    ans += dp[N - 1][i];
    ans %= MOD;
  }
  cout << ans << endl;

  return 0;
}