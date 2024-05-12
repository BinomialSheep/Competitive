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

int main() {
  /* input */
  int N;
  cin >> N;
  vl A(N);
  vl B(N);
  rep(i, N) cin >> A[i] >> B[i];

  /* solve */
  // 後ろから貪欲
  ll cnt = 0;
  for (int i = N - 1; i >= 0; i--) {
    A[i] += cnt;
    if (A[i] % B[i] != 0) {
      cnt += B[i] - A[i] % B[i];
    }
  }

  /* output */
  cout << cnt << endl;

  return 0;
}