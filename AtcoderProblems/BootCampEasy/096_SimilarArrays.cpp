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

int main() {
  // in
  int n;
  cin >> n;
  vector<int> A(n);
  rep(i, n) cin >> A[i];
  // solve
  // 全ての似ている列（3^n通り）から奇数列を引く
  int numOdd = 1;
  rep(i, n) {
    if (A[i] % 2 == 0) numOdd *= 2;
    // 奇数なら1通りなので何もしない
  }

  //
  cout << pow(3, n) - numOdd << endl;

  return 0;
}