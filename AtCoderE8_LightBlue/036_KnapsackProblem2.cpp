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

void print(vvi &dp, int i) {
  cout << i << "個目まで考慮" << endl;
  for (auto dpi : dp) {
    for (auto dpj : dpi) {
      cout << dpj << " ";
    }
    cout << endl;
  }
}

int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vi v(N);
  vi w(N);
  rep(i, N) cin >> v[i] >> w[i];

  /* solve */
  vvi dp(N + 1, vi(W + 1));
  rep(i, N) rep(j, W + 1) {
    dp[i + 1][j] = dp[i][j];
    if (j - w[i] >= 0) {
      dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - w[i]] + v[i]);
      dp[i + 1][j] = max(dp[i + 1][j], dp[i + 1][j - w[i]] + v[i]);
    }
  }

  /* output */

  cout << dp[N][W] << endl;

  return 0;
}