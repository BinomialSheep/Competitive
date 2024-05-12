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
  vector<int> X(N);
  rep(i, N) cin >> X[i];
  /* solve */
  // ソートする用
  vector<int> Y = X;
  sort(Y.begin(), Y.end());
  int s = Y[N / 2 - 1];
  int b = Y[N / 2];

  rep(i, N) {
    // 小さい値が消えた時は、大きい方の中央値候補が中央値
    // 大きい値が消えた時は、小さいの中央値候補が中央値
    if (X[i] <= s)
      cout << b << endl;
    else
      cout << s << endl;
  }

  /* output */

  return 0;
}