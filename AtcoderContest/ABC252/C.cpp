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
  int N;
  cin >> N;
  vs S(N);
  rep(i, N) cin >> S[i];

  /* solve */
  // cnt[i][j]は、数iが最初に出るのがj秒後なリールの数
  vvi cnt(10, vi(10));
  rep(i, N) {
    rep(j, 10) { cnt[S[i][j] - '0'][j]++; }
  }
  // rep(i, 10) {
  //   rep(j, 10) cout << cnt[i][j];
  //   cout << endl;
  // }

  // 何に揃えるのが最短か
  int ans = INFTY;
  rep(i, 10) {
    // iに揃えるとする
    pair<int, int> p;
    p.second = 0;
    rep(j, 10) {
      if (cnt[i][j] >= p.second) {
        p.first = j;
        p.second = cnt[i][j];
      }
    }
    // iに揃えるために掛かる時間
    int tm = p.first + 10 * (p.second - 1);
    chmin(ans, tm);
  }

  /* output */
  cout << ans << endl;

  return 0;
}