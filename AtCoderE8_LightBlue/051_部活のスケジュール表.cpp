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

int getPerson(char c) {
  if (c == 'J') return 0;
  if (c == 'O') return 1;
  if (c == 'I') return 2;
  assert(false);
  return -1;
}

int main() {
  /* input */
  int N;
  string S;
  cin >> N >> S;

  const int MOD = 10007;
  /* solve */

  // J, O, Iの順で0, 1, 2
  // dp[i][j]はi日目の人が来るのがパターンjの時の通り
  vvi dp(N + 1, vi(1 << 3));
  dp[0][1] = 1;
  //
  rep(i, N) {
    rep(bit1, (1 << 3)) {
      if (dp[i][bit1] == 0) continue;
      // ここから配るdpする
      // i+1日目に誰が来るか
      rep(bit2, (1 << 3)) {
        // 鍵を持っている人と責任者は必要
        if (!(bit2 & (1 << getPerson(S[i])))) continue;
        // 前回いた誰かが来ている必要がある
        if (!(bit1 & bit2)) continue;
        //cout << bitset<3>(bit1) << " " << bitset<3>(bit2) << endl;
        // 誰かに鍵を渡す
        dp[i + 1][bit2] += dp[i][bit1];
        dp[i + 1][bit2] %= MOD;
      }
    }
  }

  //
  int ans = 0;
  rep(bit, (1 << 3)) ans += dp[N][bit];
  ans %= MOD;

  /* output */
  cout << ans << endl;

  return 0;
}