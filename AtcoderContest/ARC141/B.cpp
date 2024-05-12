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
  int N, M;
  cin >> N >> M;

  ll MOD = 998244353;

  /* solve */
  vvl dp(N, vl(M + 1));
  rep(i, M + 1) dp[0][i] = 1;
  dp[0][0] = 0;

  // 1, 2, 4, 8, 16...と最小が狭まるので、その前のことは考えないでいい
  ll lowest = 1;
  rep(i, N - 1) {
    if (lowest * 2 > M) {
      cout << 0 << endl;
      return 0;
    }
    // 累積和処理
    vl sum(M + 1);
    ll temp = lowest * 2;
    for (ll j = lowest; j <= M; j++) {
      if (j == temp) temp *= 2;
      if (temp > M) break;
      sum[temp] += 1;
    }
    for (ll j = lowest * 2; j <= M; j++) {
      sum[j] += sum[j - 1];
      sum[j] %= MOD;
    }

    for (ll k = lowest * 2; k <= M; k++) {
      dp[i + 1][k] += sum[k];
    }

    lowest *= 2;
  }

  ll ans = 0;
  rep(i, M) {
    ans += dp[N - 1][i];
    ans %= MOD;
  }

  /* output */
  cout << ans % MOD << endl;

  return 0;
}