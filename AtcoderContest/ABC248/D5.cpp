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
  int A;
  rep(i, N) {
    scanf("%d", &A);
    myMap[A].push_back(i + 1);
  }

  int Q;
  cin >> Q;

  int L, R, X;
  vector<int> x;
  vector<int>::iterator l;
  vector<int>::iterator r;
  vector<unordered_map<pair<int, int>, vector<int>::iterator>> memo;
  rep(i, Q) {
    scanf("%d %d %d", &L, &R, &X);
    // cin >> L >> R >> X;
    x = myMap[X];
    auto pl = make_pair(x, l);
    auto pr = make_pair(x, r);
    if (memo[pl]) {
      memo[pl] = lower_bound(x.begin(), x.end(), L);
    }
    // if (l == x.end()) {
    //   printf("0\n");
    // } else {
    if (!memo[pr]) {
      memo[pr] = upper_bound(x.begin(), x.end(), R);
    }
    printf("%d\n", distance(memo[pl], memo[pr]));
    //}
  }
  cout << flush;

  /* output */

  return 0;
}