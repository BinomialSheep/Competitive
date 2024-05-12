#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
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
  int n, m;
  cin >> n >> m;
  vector<int> A(n + 1);
  vector<int> C(n + m + 1);
  rep(i, n + 1) cin >> A[i];
  rep(i, n + m + 1) cin >> C[i];

  /* solve */
  // Bはm次の多項式になる
  vector<int> B(m + 1, 0);
  for (int i = m; i >= 0; i--) {
    // i桁目を求める
    int k = C[i + n] / A[n];
    B[i] = k;
    rep(j, n + 1) { C[i + j] -= k * A[j]; }

    // //
    // cout << "debug:";
    // rep(i, n + m + 1) cout << C[i] << " ";
    // cout << endl;
  }

  /* output */
  rep(i, m + 1) cout << B[i] << " ";
  cout << endl;

  return 0;
}