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

// LIS: Longest Increasing Subsequence
int main() {
  /* input */
  int n;
  cin >> n;
  vi a(n);
  rep(i, n) cin >> a[i];

  /* solve */
  // 長さがi+1であるような増加部分列における最終要素の最小値
  vi dp(n, (1 << 30));
  dp[0] = a[0];
  int length = 1;

  for (int i = 1; i < n; i++) {
    if (dp[length - 1] < a[i]) {
      // 長さを1増やす
      dp[length] = a[i];
      length++;
    } else {
      // a[i]以上になる最小のindexを探す
      *lower_bound(dp.begin(), dp.end(), a[i]) = a[i];
    }
  }

  /* output */
  rep(i, n) {
    if (dp[i] == (1 << 30)) {
      cout << i << endl;
      return 0;
    }
  }
  cout << n << endl;

  return 0;
}
