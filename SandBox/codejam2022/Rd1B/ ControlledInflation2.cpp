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
  ll T;
  cin >> T;

  /* solve */
  rep(i, T) {
    ll N, P;
    cin >> N >> P;
    vector<vector<int>> x(N, vector<int>(P));
    rep(j, N) rep(k, P) cin >> x[j][k];
    // sortしておく
    rep(j, N) { sort(x[j].begin(), x[j].end()); }
    ll ans = 0;
    // 顧客ごとに絶対かかる時間
    rep(j, N) { ans += x[j][P - 1] - x[j][0]; }
    // cout << ans << endl;

    // cout << ans << endl;
    //  顧客間に掛かる時間をdp
    //  x人目を終えてyの時の最小値を求めていく
    vector<vector<ll>> dp(N, vector<ll>(2));
    dp[0][0] = x[0][P - 1];
    dp[0][1] = x[0][0];
    rep(j, N - 1) {
      ll l1 = x[j][0];
      ll l2 = x[j][P - 1];
      ll n1 = x[j + 1][0];
      ll n2 = x[j + 1][P - 1];

      // 直前で→1を選んだ場合、次は0→になる
      dp[j + 1][0] = llMin(dp[j][0] + abs(n2 - l1), dp[j][1] + abs(n2 - l2));
      dp[j + 1][1] = llMin(dp[j][0] + abs(n1 - l1), dp[j][1] + abs(n1 - l2));

      // cout << "dp[i][n1], d[i][n2]:" << j + 1 << " " << dp[j + 1][0] << " "
      //      << dp[j + 1][1] << endl;
    }

    ll d1 = dp[N - 1][0];
    ll d2 = dp[N - 1][1];
    // cout << d1 << " " << d2;

    ans += llMin(d1, d2);

    cout << "Case #" << i + 1 << ": ";
    cout << ans << endl;
  }

  /* output */

  return 0;
}