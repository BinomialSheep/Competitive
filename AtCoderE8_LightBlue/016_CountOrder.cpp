#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include <atcoder/all>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)
ll llMax(ll x, ll y) { return (x >= y) ? x : y; }
ll llMin(ll x, ll y) { return (x <= y) ? x : y; }

bool isSame(vector<int> A, vector<int> B) {
  rep(i, A.size()) {
    if (A[i] != B[i]) return false;
  }
  return true;
}

int main() {
  /* input */
  int N;
  cin >> N;
  vector<int> P(N), Q(N);
  rep(i, N) cin >> P[i];
  rep(i, N) cin >> Q[i];

  /* solve */
  int a, b;
  vector<int> ord(N);
  rep(i, N) ord[i] = i + 1;
  int index = 1;
  do {
    if (isSame(P, ord)) a = index;
    if (isSame(Q, ord)) b = index;
    index++;
  } while (next_permutation(ord.begin(), ord.end()));

  /* output */
  cout << abs(a - b) << endl;

  return 0;
}