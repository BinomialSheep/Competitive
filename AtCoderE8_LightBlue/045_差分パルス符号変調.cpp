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
  while (true) {
    /* input */
    int N, M;
    cin >> N >> M;
    if (N == 0 && M == 0) break;
    vi C(M);
    rep(i, M) cin >> C[i];
    vi x(N);
    rep(i, N) cin >> x[i];

    /* solve */
    // dp[i][j]は、i番目まで圧縮し終え、yの値がjの時の最小の自乗誤差
    vvi dp(N + 1, vi(256, INFTY));
    dp[0][128] = 0;
    rep(i, N) {
      rep(j, 256) {
        // if (dp[i][j] == INFTY) continue;
        rep(k, M) {
          int y = j + C[k];
          if (y < 0) y = 0;
          if (y > 255) y = 255;
          chmin(dp[i + 1][y], dp[i][j] + (int)pow(x[i] - y, 2));
        }
      }
    }

    // rep(i, N + 1) {
    //   rep(j, 256) {
    //     if (dp[i][j] == INFTY) continue;
    //     printf("%d %d %d\n", i, j, dp[i][j]);
    //   }
    // }

    /* output */
    int ans = INFTY;
    rep(i, 256) chmin(ans, dp[N][i]);
    cout << ans << endl;
  }

  return 0;
}