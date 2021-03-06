#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
  vector<int> A(N);
  rep(i, N) cin >> A[i];
  int Q;
  cin >> Q;
  vector<int> M(Q);
  rep(i, Q) cin >> M[i];

  /* solve */
  set<int> ansSet;
  for (int bit = 0; bit < (1 << N); bit++) {
    int sum = 0;
    rep(i, N) {
      if (bit & (1 << i)) sum += A[i];
    }
    ansSet.insert(sum);
  }
  /* output */
  rep(i, Q) { cout << (ansSet.count(M[i]) != 0 ? "yes" : "no") << endl; }

  return 0;
}