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

// 普通の素数判定(O(log(√N)))
bool isPrimeSimple(long long N) {
  if (N == 1) return false;
  for (long long i = 2; i * i <= N; ++i) {
    if (N % i == 0) return false;
  }
  return true;
}

int main() {
  /* input */
  ll N, P;
  cin >> N >> P;

  /* solve */
  // P <= 10^12より、40 <= Nならaに必ず1が含まれる
  if (N >= 40) {
    cout << 1 << endl;
    return 0;
  }
  if (N == 1) {
    cout << P << endl;
    return 0;
  }

  // 2にできるか、3にできるか…… Pのn乗根にできるかを考える
  ll ans = 1;
  for (ll i = 2;; i++) {
    ll temp = (ll)pow(i, N);
    if (temp > P) break;
    if (P % temp == 0) ans = i;
  }

  /* output */
  cout << ans << endl;

  return 0;
}