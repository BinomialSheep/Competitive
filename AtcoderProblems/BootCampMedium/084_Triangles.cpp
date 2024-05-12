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

set<ll> mySet;

int main() {
  /* input */
  int N;
  cin >> N;
  vector<ll> L(N);
  rep(i, N) cin >> L[i];

  /* solve */
  sort(L.begin(), L.end());
  ll ans = 0;
  rep(i, N - 2) {
    for (int j = i + 1; j < N - 1; j++) {
      auto it = lower_bound(L.begin(), L.end(), L[i] + L[j]);
      if (it == L.end() && j == N - 1) continue;
      int d = (int)distance(L.begin(), it);
      ans += d - j - 1;
    }
  }

  /* output */
  cout << ans << endl;

  return 0;
}