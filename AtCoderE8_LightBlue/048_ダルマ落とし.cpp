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
    int n;
    cin >> n;
    if (n == 0) break;
    vi w(n);
    rep(i, n) cin >> w[i];

    /* solve */
    // dp[i][j]は、iからjまでの求める最大個数
    vvi dp(n, vi(n));

    for (int diff = 1; diff < n; diff++) {
      rep(i, n - diff) {
        int j = i + diff;
        assert(i < j && j < n);
        // 間が1個ならやるだけ
        if (j - i == 1) {
          if (abs(w[j] - w[i]) <= 1) dp[i][j] = 2;
          continue;
        }
        if (j - i >= 3) {
          // i+1からj-1まで全部消せる時だけiとjまで全消しの可能性がある
          if (dp[i + 1][j - 1] == j - i - 1) {
            if (abs(w[j] - w[i]) <= 1) dp[i][j] = j - i + 1;
            // cout << "iとj全消し：" << i << " " << j << endl;
          }
        }
        // dp[i][k] + dp[k+1][j]のmaxを考えればいい
        for (int k = i; k < j; k++) {
          chmax(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
      }
    }

    // rep(i, n - 1) {
    //   for (int j = i + 1; j < n; j++) {
    //     cout << dp[i][j] << " ";
    //   }
    //   cout << endl;
    // }

    /* output */

    cout << dp[0][n - 1] << endl;
  }

  return 0;
}