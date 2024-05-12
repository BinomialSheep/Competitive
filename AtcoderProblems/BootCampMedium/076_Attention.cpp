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
  string S;
  cin >> N >> S;

  /* solve */
  vi left(N);
  rep(i, N) {
    if (i == 0)
      left[0] = (S[0] == 'W' ? 1 : 0);
    else if (S[i] == 'W')
      left[i] = left[i - 1] + 1;
    else
      left[i] = left[i - 1];
    // cout << left[i];
  }
  // cout << endl;
  int ans = INFTY;
  rep(i, N) {
    // i人目をリーダーにした時に向く方向を変える数
    int cnt = 0;
    // i-1人目までで左を向いている人が右を向く
    if (i != 0) cnt += left[i - 1];
    // i+1人目以降で右を向いている人が左を向く
    if (i != N - 1) {
      int l = left[N - 1] - left[i];
      int al = N - i - 1;
      int r = al - l;
      cnt += r;
      // cout << i << l << al << r << endl;
    }
    // 更新
    // cout << cnt << endl;
    chmin(ans, cnt);
  }

  /* output */
  cout << ans << endl;

  return 0;
}