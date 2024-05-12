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
  //
  vvl dp(N, vl(M));

  rep(i, M) dp[0][i] = 1;

  rep(i, N - 1) {

    // j以下

    // j以上
    

    rep(j, M) {


      if (j + K <= M - 1) {
        for (int l = j + K; l <= M - 1; l++) {
          dp[i + 1][l] += dp[i][j];
          dp[i + 1][l] %= MOD;
        }
      }
      if (0 <= j - K) {
        for (int l = j - K; l >= 0; l--) {
          dp[i + 1][l] += dp[i][j];
          dp[i + 1][l] %= MOD;
        }
      }
    }
  }

  ll cnt = 0;
  rep(j, M) {
    cnt += dp[N - 1][j];
    cnt %= MOD;
  }
  /* output */
  cout << cnt << endl;

  return 0;
}