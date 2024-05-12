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

ll stupid(int n, vi &r, vi &c) {
  // 順列全探索する
  // 掛け算を行う位置
  vi perm(n - 1);
  rep(i, n - 1) perm[i] = i;
  ll ret = INFTY;
  do {
    vi r2 = r;
    vi c2 = c;

    ll cnt = 0;
    vector<bool> used(n - 1, false);
    rep(i, n - 1) {
      cnt += (ll)r2[perm[i]] * c2[perm[i]] * c2[perm[i] + 1];
      // 行数と列数を更新する
      used[perm[i]] = true;
      for (int j = perm[i]; j < n - 1; j++) {
        if (!used[j]) break;
        r2[j + 1] = r2[j];
      }
      for (int j = perm[i]; j >= 0; j--) {
        if (!used[j]) break;
        c2[j] = c2[j + 1];
      }
    }
    // rep(i, n - 1) cout << perm[i];
    // cout << " r:";
    // rep(i, n) cout << r2[i] << " ";
    // cout << " c:";
    // rep(i, n) cout << c2[i] << " ";
    // cout << " " << cnt << endl;
    chmin(ret, cnt);
  } while (next_permutation(perm.begin(), perm.end()));
  return ret;
}

ll calc(int left, int right, vi &r, vi &c, vvl &dp) {
  // cout << left << " " << right << endl;
  assert(right - left >= 1);
  if (dp[left][right] != INFTY) return dp[left][right];
  if (right - left == 1) return 0;

  if (right - left == 2) {
    dp[left][right] = r[left] * c[left] * c[left + 1];
    return dp[left][right];
  }

  for (int k = left + 1; k < right; k++) {
    ll now = (ll)r[left] * c[k - 1] * c[right - 1];
    dp[left][k] = calc(left, k, r, c, dp);
    dp[k][right] = calc(k, right, r, c, dp);
    chmin(dp[left][right], dp[left][k] + dp[k][right] + now);
    // cout << left << k << right << " " << dp[left][right] << endl;
  }
  return dp[left][right];
}

ll solve(int n, vi &r, vi &c) {
  // dp[i][j]は、[i, j)の最小
  vvl dp(n + 1, vl(n + 1, INFTY));
  return calc(0, n, r, c, dp);
}

// 連鎖行列積
// 区間DP
int main() {
  /* input */
  int n;
  cin >> n;
  vi r(n), c(n);
  rep(i, n) cin >> r[i] >> c[i];

  /* solve */
  ll ans;

  // ans = stupid(n, r, c);
  ans = solve(n, r, c);

  /* output */
  cout << ans << endl;

  return 0;
}