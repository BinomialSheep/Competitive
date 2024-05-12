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
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int q;
  cin >> q;
  vs X(q);
  vs Y(q);
  rep(i, q) cin >> X[i] >> Y[i];

  /* solve */
  rep(i, q) {
    string x = X[i];
    string y = Y[i];
    vvi dp(x.size() + 1, vi(y.size() + 1));

    rep(j, x.size()) {
      rep(k, y.size()) {
        if (x[j] == y[k]) {
          dp[j + 1][k + 1] = dp[j][k] + 1;
        } else {
          dp[j + 1][k + 1] = max(dp[j + 1][k], dp[j][k + 1]);
        }
      }
    }
    cout << dp[x.size()][y.size()] << endl;
  }

  /* output */

  return 0;
}