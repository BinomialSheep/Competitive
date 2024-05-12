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

void print(vvi &dp, int i) {
  cout << i << "個目まで考慮" << endl;
  for (auto dpi : dp) {
    for (auto dpj : dpi) {
      cout << dpj << " ";
    }
    cout << endl;
  }
}

int main() {
  /* input */
  int N, W;
  cin >> N >> W;
  vi v(N);
  vi w(N);
  rep(i, N) cin >> v[i] >> w[i];

  /* solve */
  // 同じ重さなら1番価値の高いものだけあれば十分
  map<int, int> mp;
  rep(i, N) { mp[w[i]] = max(mp[w[i]], v[i]); }
  // 
  vvi dp((int)mp.size() + 1, vi(W + 1));
  int idx = 0;
  for (auto p : mp) {
    rep(j, W + 1) {
      dp[idx + 1][j] = dp[idx][j];
      rep(k, INFTY) {
        // k個選ぶ
        int ww = p.first;
        int vv = p.second;
        if (j - ww * k < 0) break;
        dp[idx + 1][j] = max(dp[idx + 1][j], dp[idx][j - ww * k] + vv * k);
      }
    }
    idx++;
  }

  /* output */
  int ans = 0;
  rep(i, W + 1) ans = max(ans, dp[(int)mp.size()][i]);
  cout << ans << endl;

  return 0;
}