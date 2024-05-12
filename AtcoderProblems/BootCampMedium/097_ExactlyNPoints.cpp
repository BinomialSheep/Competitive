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

  if (N == 1 || N == 2) {
    cout << N << endl;
    return 0;
  }

  /* solve */
  // 1点は1まで, 2-3点は2まで、4-6点は3まで、7-10点は4までで可能

  vi prefixSum(1e6);

  for (int i = 1; i < N; i++) {
    prefixSum[i] = prefixSum[i - 1] + i;
    if (prefixSum[i] >= N) {
      prefixSum.resize(i + 1);
      break;
    }
  }
  while (N >= 0) {
    auto it = lower_bound(prefixSum.begin(), prefixSum.end(), N);

    int d = (int)distance(prefixSum.begin(), it);
    if (d == 0) break;

    cout << d << endl;
    N -= d;
  }

  /* output */

  return 0;
}