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

// 繰り返し自乗法によるx^nの高速計算(O(logn))
// x^2n = (x^2)^nおよびx^2(m-1) = 2 * x^2mを利用
// Mは大きな素数(1000000007など)
ll myPow(ll x, ll n, ll M) {
  ll res = 1;
  if (n > 0) {
    res = myPow(x, n / 2, M);
    if (n % 2 == 0)
      res = (res * res) % M;
    else
      res = (((res * res) % M) * x) % M;
  }
  return res;
}

int main() {
  int m, n;
  cin >> m >> n;
  static const ll MOD = 1000000007;
  cout << myPow(m, n, MOD) << endl;

  return 0;
}