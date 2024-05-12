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

// 計算量はO(N+log(a'))になるらしい。ただしa'はAで2番目に大きい数
template <class T>
T gcd_vec(vector<T> &A) {
  int size = (int)A.size();
  T ret = A[0];
  for (int i = 1; i < size; i++) {
    ret = gcd(ret, A[i]);
  }
  return ret;
}

// std::gcdがある
int myGcd(int x, int y) {
  if (x < y) swap(x, y);
  int r;
  while (y > 0) {
    r = x % y;
    x = y;
    y = r;
  }
  return x;
}

int main() {
  int a, b;
  cin >> a >> b;
  cout << myGcd(a, b) << endl;

  return 0;
}