#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

int main() {
  /* input */
  int n, q;
  cin >> n;
  vector<int> S(n);
  rep(i, n) cin >> S[i];
  cin >> q;
  vector<int> T(q);
  rep(i, q) cin >> T[i];

  /* solve */
  int C = 0;
  // 二分探索で解く
  rep(i, q) {
    if (binary_search(S.begin(), S.end(), T[i])) C++;
  }

  /* output */
  cout << C << endl;

  return 0;
}