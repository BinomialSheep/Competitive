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

void print(vvi &dp, int N) {
  rep(i, N + 1) {
    rep(j, 3) cout << dp[i][j] << " ";
    cout << endl;
  }
}

int main() {
  /* input */
  int N;
  cin >> N;
  vs S(5);
  rep(i, 5) cin >> S[i];

  /* solve */
  // dp[i][j]は、i列目まで塗り終えて、i列目が色jの時の塗り替えるマスの個数の最小値
  vvi dp(N + 1, vi(3, INFTY));
  rep(j, 3) dp[0][j] = 0;
  rep(i, N) {
    rep(j, 3) {
      // i列目まで塗り終えて、i列目が色j
      vi cnt(3);
      rep(c, 5) {
        if (S[c][i] == 'R') cnt[0]++;
        if (S[c][i] == 'B') cnt[1]++;
        if (S[c][i] == 'W') cnt[2]++;
      }
      // cout << cnt[0] << cnt[1] << cnt[2] << endl;
      rep(k, 3) {
        // i+1列目をk色に塗る
        // 同じ色には塗れない
        if (j == k) continue;
        if (dp[i][k] == INFTY) continue;
        chmin(dp[i + 1][k], dp[i][j] + (5 - cnt[k]));
      }
    }
  }
  //
  int ans = INFTY;
  rep(i, 3) chmin(ans, dp[N][i]);
  cout << ans << endl;

  // debug
  // print(dp, N);

  /* output */

  return 0;
}