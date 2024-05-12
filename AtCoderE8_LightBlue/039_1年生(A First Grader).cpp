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
  int N;
  cin >> N;
  vi M(N + 1);
  rep(i, N) cin >> M[i + 1];

  /* solve */
  // i桁目まで考慮した時の値がjになる個数
  vvl dp(N + 1, vl(21));
  rep(i, N - 1) {
    if (i == 0) {
      dp[1][M[1]] = 1;
      continue;
    }
    rep(j, 21) {
      if (dp[i][j] == 0) continue;
      if (j + M[i + 1] <= 20) {
        dp[i + 1][j + M[i + 1]] += dp[i][j];
      }
      if (j - M[i + 1] >= 0) {
        dp[i + 1][j - M[i + 1]] += dp[i][j];
      }
    }
  }

  /* output */
  cout << dp[N - 1][M[N]] << endl;

  return 0;
}