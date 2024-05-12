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

void print(vvi &dp, int D, int N) {
  rep(i, D) {
    rep(j, N) {
      //
      cout << dp[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {
  /* input */
  int D, N;
  cin >> D >> N;
  vi T(D);
  rep(i, D) cin >> T[i];
  vi A(N), B(N), C(N);
  rep(i, N) cin >> A[i] >> B[i] >> C[i];

  /* solve */
  // i日目が終わって、最後に着た服がjだった時の、ここまでの派手さの絶対値の合計のMAX
  vvi dp(D, vi(N, -1));
  rep(i, D) {
    if (i == 0) {
      rep(j, N) {
        if (T[i] < A[j] || B[j] < T[i]) continue;
        dp[i][j] = 0;
      }
      continue;
    }
    // 今日着る服
    rep(j, N) {
      if (T[i] < A[j] || B[j] < T[i]) continue;
      // 昨日着た服
      rep(k, N) {
        // あり得ないパターンは除外
        if (dp[i - 1][k] == -1) continue;
        dp[i][j] = max(dp[i][j], dp[i - 1][k] + abs(C[j] - C[k]));
      }
    }
  }
  //
  int ans = 0;
  rep(j, N) ans = max(ans, dp[D - 1][j]);

  // print(dp, D, N);

  /* output */
  cout << ans << endl;

  return 0;
}