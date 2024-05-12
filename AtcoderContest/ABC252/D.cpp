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

ll nC2(int n) {
  ll ret;
  if (n < 2) return 0;
  ret = (ll)n * (n - 1) / 2;
  return ret;
}

int main() {
  /* input */
  int N;
  cin >> N;
  vi A(N);
  rep(i, N) cin >> A[i];

  /* solve */

  // ある数が出た回数を覚えておく
  map<int, int> mp;
  mp[A[0]]++;
  mp[A[1]]++;

  ll ans = 0;
  ll dup = 0;
  for (int k = 2; k < N; k++) {
    // 計算パート
    // (k-自分自身の被り)C2 - (被り)
    int cnt = mp[A[k]];
    if (k - cnt >= 2) {
      ans += nC2(k - cnt);
      ans -= (dup - nC2(cnt));
    }
    // 挿入パート
    mp[A[k]] = cnt + 1;
    // 重複計算
    dup -= nC2(cnt);
    dup += nC2(cnt + 1);
    // cout << ans << " ";
  }

  /* output */
  cout << ans << endl;

  return 0;
}