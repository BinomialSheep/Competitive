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

ll sum(ll M, ll N) {
  // 初項M
  // 項数
  ll num = N / M;
  // 末項
  ll last = M * num;

  ll ret = num * (last + M) / 2;

  return ret;
}

int main() {
  /* input */
  ll N, A, B;
  cin >> N >> A >> B;

  /* solve */
  ll AB = lcm(A, B);
  // Aの倍数の和 + Bの倍数の和 - ABの倍数
  ll aSum = sum(A, N);
  ll bSum = sum(B, N);
  ll abSum = sum(AB, N);

  // 1からNの総和
  ll nNum = N * (N + 1) / 2;

  ll ans = nNum - aSum - bSum + abSum;

  /* output */
  cout << ans << endl;

  return 0;
}