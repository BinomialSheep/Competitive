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
#define INFTY (1 << 30)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

template <typename T>
inline bool chmax(T &a, T b) {
  return ((a < b) ? (a = b, true) : (false));
}
template <typename T>
inline bool chmin(T &a, T b) {
  return ((a > b) ? (a = b, true) : (false));
}

int main() {
  /* input */
  int N, M;
  cin >> N >> M;
  vi D(N);
  rep(i, N) cin >> D[i];
  vi C(M);
  rep(i, M) cin >> C[i];

  /* solve */
  // dp[i][j] i日目を終えて都市jにいる時の疲労度
  vvi dp(M + 1, vi(N + 1, INFTY));
  // init
  dp[0][0] = 0;
  //
  rep(i, M) {
    rep(j, N) {
      // i日目を終えて都市jにいるとする
      // ありえない話し！
      if (dp[i][j] == INFTY) continue;
      // 移動
      chmin(dp[i + 1][j + 1], dp[i][j] + D[j] * C[i]);
      // 移動しない
      chmin(dp[i + 1][j], dp[i][j]);
    }
  }

  int ans = INFTY;
  rep(i, M + 1) chmin(ans, dp[i][N]);

  /* output */
  cout << ans << endl;

  return 0;
}