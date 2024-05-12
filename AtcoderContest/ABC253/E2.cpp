#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vl = vector<long long>;
using vs = vector<string>;
using vc = vector<char>;
using vb = vector<bool>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;
using vvi = vector<vector<int>>;
using vvl = vector<vector<long long>>;
using vvc = vector<vector<char>>;
using vvb = vector<vector<bool>>;
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
  ll N, M, K;
  cin >> N >> M >> K;

  ll MOD = 998244353;

  /* solve */
  if (M == 1) {
    cout << 1 << endl;
    return 0;
  }
  if (K == 0) {
    ll ans = 1;
    rep(i, N) {
      ans *= M;
      ans %= MOD;
    }
    cout << ans << endl;
    return 0;
  }

  //
  vvl dp(N, vl(M));

  rep(i, M) dp[0][i] = 1;

  rep(i, N - 1) {
    // j以下
    vl underSum(M);
    underSum[0] = dp[i][0];
    for (int j = 1; j < M; j++) {
      underSum[j] = underSum[j - 1] + dp[i][j];
      underSum[j] %= MOD;
    }
    rep(j, M) {
      // 下がってくる
      if (j + K < M) {
        ll overSum = MOD + underSum[M - 1] - underSum[j + K - 1];
        dp[i + 1][j] += overSum;
      }
      // 上がってくる
      if (0 <= j - K) {
        dp[i + 1][j] += underSum[j - K];
      }
      dp[i + 1][j] %= MOD;
    }
  }

  ll cnt = 0;
  rep(j, M) {
    cnt += dp[N - 1][j];
    cnt %= MOD;
  }
  /* output */
  cout << (cnt % MOD) << endl;

  return 0;
}