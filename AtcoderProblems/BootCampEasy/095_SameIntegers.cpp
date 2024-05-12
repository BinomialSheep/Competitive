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
  vector<int> vec(3);
  rep(i, 3) cin >> vec[i];
  sort(vec.begin(), vec.end());
  int a = vec[0], b = vec[1], c = vec[2];
  // solve
  int count = 0;
  // まずbをcを+1で等しくする
  while (b < c) {
    a++;
    b++;
    count++;
  }
  // aとcの差が1以下になるまで+2する
  while (a != c && a != c - 1) {
    a += 2;
    count++;
  }
  // 等しくなっていない（つまりa+1 == b == c）ならb,cを+1してからaを+2する
  if (a != c) count += 2;

  //
  cout << count << endl;

  return 0;
}