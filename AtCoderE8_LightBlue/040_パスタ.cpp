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

int main() {
  /* input */
  int N, K;
  cin >> N >> K;
  vi decided(N, -1);
  rep(i, K) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;
    decided[a] = b;
  }

  /* solve */
  const int MOD = 10000;
  // dp[i][j][k]は、iまで終わった時点で今回がj, 直前がkの時の組み合わせ数
  vector<vvi> dp(N, vvi(3, vi(3)));
  rep(i, N) {
    if (i == 0) {
      if (decided[i] == -1) {
        dp[i][0][0] = 1;
        dp[i][1][0] = 1;
        dp[i][2][0] = 1;
      } else {
        dp[i][decided[i]][0] = 1;
      }
      continue;
    }
    if (i == 1) {
      if (decided[i] == -1) {
        rep(j, 3) {
          rep(k, 3) {
            //
            dp[i][j][k] += dp[i - 1][k][0];
          }
        }
      } else {
        rep(k, 3) {
          //
          dp[i][decided[i]][k] += dp[i - 1][k][0];
        }
      }
      continue;
    }
    //
    if (decided[i] == -1) {
      rep(h, 3) {
        rep(j, 3) {
          rep(k, 3) {
            // 今回h、前回j、前々回k
            if (h == j && j == k) continue;
            dp[i][h][j] += dp[i - 1][j][k];
            dp[i][h][j] %= MOD;
          }
        }
      }
    } else {
      rep(j, 3) {
        rep(k, 3) {
          // 今回decided[i]、前回j、2つ前k
          if (decided[i] == j && j == k) continue;
          // printf("%d %d %d %d\n", i, decided[i], j, k);
          dp[i][decided[i]][j] += dp[i - 1][j][k];
          dp[i][decided[i]][j] %= MOD;
        }
      }
    }
  }
  //
  int ans = 0;
  rep(j, 3) rep(k, 3) {
    //
    ans += dp[N - 1][j][k];
  }

  /* output */
  cout << ans % MOD << endl;

  return 0;
}