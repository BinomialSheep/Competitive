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
  vector<pair<int, int>> A;
  unordered_map<int, int> myMap;
  rep(i, N) {
    int a;
    scanf("%d", &a);
    myMap[a]++;
    A.emplace_back(a, myMap[a]);
  }

  int Q;
  cin >> Q;

  rep(i, Q) {
    int L, R, X;
    scanf("%d %d %d", &L, &R, &X);

    auto l = lower_bound(A.begin(), A.end(), X);
    if (l == x.end()) {
      printf("0\n");
    } else {
      auto r = upper_bound(A.begin(), A.end(), X);
      printf("%d\n", (int)distance(l, r));
    }
  }
  cout << flush;

  /* output */

  return 0;
}