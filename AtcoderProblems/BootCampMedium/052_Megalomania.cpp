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
  int N;
  cin >> N;
  vector<pair<int, int>> BA(N);
  rep(i, N) {
    int A, B;
    cin >> A >> B;
    BA[i] = make_pair(B, A);
  }

  /* solve */
  sort(BA.begin(), BA.end());
  ll time = 0;
  rep(i, N) {
    time += BA[i].second;
    if (time > BA[i].first) {
      cout << "No" << endl;
      return 0;
    }
  }
  cout << "Yes" << endl;

  /* output */

  return 0;
}