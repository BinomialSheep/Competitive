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

// 0-1ナップザック問題
int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vpii vw(N);
  rep(i, N) {
    int v, w;
    cin >> v >> w;
    vw[i] = make_pair(v, w);
  }

  /* solve */
  // i個目まで考慮して、重さj以下になる時の価値の最大値がdp[i][j]
  vvi dp(N + 1, vi(W + 1));
  for (int i = 1; i <= N; i++) {
    int v = vw[i - 1].first;
    int w = vw[i - 1].second;
    rep(j, W + 1) {
      if (j - w < 0) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
      }
    }
  }
  /* output */
  cout << dp[N][W] << endl;

  return 0;
}