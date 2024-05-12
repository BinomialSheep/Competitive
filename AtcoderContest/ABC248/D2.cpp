#include <bits/stdc++.h>
using namespace std;
using ll = long long;
//#include <atcoder/all>
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

  /* solve */
  unordered_map<int, vector<int>> myMap;
  rep(i, N) {
    int A;
    cin >> A;
    myMap[A].push_back(i + 1);
  }

  int Q;
  cin >> Q;

  rep(i, Q) {
    int L, R, X;
    cin >> L >> R >> X;
    auto l = lower_bound(myMap[X].begin(), myMap[X].end(), L);

    auto r = lower_bound(myMap[X].begin(), myMap[X].end(), R + 1);
    cout << distance(l, r) << endl;
  }

  /* output */

  return 0;
}