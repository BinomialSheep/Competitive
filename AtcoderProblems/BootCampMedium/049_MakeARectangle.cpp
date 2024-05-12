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
  vector<int> A(N);
  rep(i, N) cin >> A[i];

  /* solve */
  sort(A.rbegin(), A.rend());

  int last = -1;
  vector<int> B(2);
  int index = 0;
  rep(i, N) {
    if (A[i] == last) {
      B[index] = A[i];
      last = -1;
      index++;
      if (index == 2) break;
    } else {
      last = A[i];
    }
  }

  /* output */
  cout << (ll)B[0] * B[1] << endl;

  return 0;
}