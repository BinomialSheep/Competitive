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
  int A, B, C, D, E, F, X;
  cin >> A >> B >> C >> D >> E >> F >> X;

  /* solve */
  int walk = A;
  int stay = 0;
  int t = 0;
  for (int i = 1; i <= X; i++) {
    if (walk >= 2) {
      walk--;
      t += B;
    } else if (walk == 1) {
      walk--;
      t += B;
      stay = C;
    } else if (stay >= 2) {
      //
      stay--;
      continue;
    } else if (stay == 1) {
      stay--;
      walk = A;
    }
  }
  walk = D;
  stay = 0;
  int a = 0;
  for (int i = 1; i <= X; i++) {
    if (walk >= 2) {
      walk--;
      a += E;
    } else if (walk == 1) {
      walk--;
      a += E;
      stay = F;
    } else if (stay >= 2) {
      //
      stay--;
      continue;
    } else if (stay == 1) {
      stay--;
      walk = D;
    }
  }

  /* output */
  if (t > a) {
    cout << "Takahashi" << endl;
  } else if (t < a) {
    cout << "Aoki" << endl;
  } else {
    cout << "Draw" << endl;
  }

  return 0;
}