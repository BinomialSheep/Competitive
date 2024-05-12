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
  int N, M;
  cin >> N >> M;
  unordered_set<int> a;
  rep(i, M) {
    int temp;
    cin >> temp;
    a.insert(temp);
  }

  ll MOD = 1e9 + 7;

  /* solve */
  vl dp(N + 1);
  dp[0] = 1;

  rep(i, N) {
    if (a.count(i + 1) == 0) {
      dp[i + 1] += dp[i];
      dp[i + 1] %= MOD;
    }
    if (i + 2 <= N && a.count(i + 2) == 0) {
      dp[i + 2] += dp[i];
      dp[i + 2] %= MOD;
    }
  }

  /* output */
  cout << dp[N] << endl;

  return 0;
}