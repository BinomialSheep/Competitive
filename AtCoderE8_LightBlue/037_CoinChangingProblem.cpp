#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvvi = vector<vector<vector<int>>>;
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
  int n, m;
  cin >> n >> m;
  vi c(m);
  rep(i, m) cin >> c[i];

  /* solve */
  sort(c.rbegin(), c.rend());
  // dp[i][j]は、i種類目までのコインを使ってj円を払う最小枚数
  vvi dp(m + 1, vi(n + 1, INFTY));
  rep(i, m + 1) dp[i][0] = 0;
  rep(i, m) {
    rep(j, n + 1) {
      dp[i + 1][j] = dp[i][j];
      if (j - c[i] < 0) continue;
      dp[i + 1][j] = min(dp[i + 1][j], dp[i][j - c[i]] + 1);
      dp[i + 1][j] = min(dp[i + 1][j], dp[i + 1][j - c[i]] + 1);
    }
  }

  /* output */
  cout << dp[m][n] << endl;

  return 0;
}