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
  int D;
  cin >> D;
  vi c(26);
  rep(i, 26) cin >> c[i];
  vvi s(D, vi(26));
  rep(i, D) rep(j, 26) cin >> s[i][j];

  //
  vi t(D);
  rep(i, D) {
    cin >> t[i];
    --t[i];
  }

  /* solve */

  // last[i]はコンテストiが最後に開催された日
  vi last(26);

  vl v(D);
  ll score = 0;

  rep(i, D) {
    // d日目はt[i]が開催される
    //　上がる分
    score += s[i][t[i]];
    // lastの更新
    last[t[i]] = i + 1;
    // 下がる分
    rep(j, 26) {
      //
      score -= c[j] * (i + 1 - last[j]);
    }
    v[i] = score;
  }

  /* output */
  rep(i, D) cout << v[i] << endl;

  return 0;
}