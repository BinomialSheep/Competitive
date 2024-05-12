#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;
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

int calcDivNum(ll M) {
  int ret = 0;
  while (M != 1) {
    M /= 2;
    ret++;
  }
  return ret;
}

int main() {
  /* input */
  ll N, M;
  cin >> N >> M;

  ll MOD = 998244353;

  if (N >= 62) {
    cout << 0 << endl;
    return 0;
  }

  /* solve */
  // 何回割れるか求める
  int divNum = calcDivNum(M);
  //
  vl powList(divNum + 2);
  powList[0] = 1;
  for (int i = 1; i < divNum + 1; i++) powList[i] = powList[i - 1] * 2;
  powList[(int)powList.size() - 1] = M + 1;

  vvl dp(N, vl(divNum + 1));
  rep(i, divNum + 1) { dp[0][i] = powList[i + 1] - powList[i]; }

  rep(i, N - 1) {
    rep(j, divNum) {
      for (int k = j + 1; k <= divNum; k++) {
        ll mul = powList[k + 1] - powList[k];
        mul %= MOD;

        dp[i + 1][k] += dp[i][j] * mul;
        dp[i + 1][k] %= MOD;
        // cout << i + 1 << " " << k << " " << dp[i + 1][k] << endl;
        // if (i == 0 && k == 2) {
        //   cout << i << " " << j << " " << mul << " " << dp[i + 1][k] << endl;
        // }
      }
    }
  }

  ll ans = 0;
  rep(i, divNum + 1) {
    // cout << i << " " << dp[N - 1][i] << endl;
    ans += dp[N - 1][i];
    ans %= MOD;
  }

  /* output */
  cout << ans % MOD << endl;

  return 0;
}