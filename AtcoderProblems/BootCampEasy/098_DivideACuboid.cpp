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
  ll a, b, c;
  cin >> a >> b >> c;
  // solve
  // 条件よりどこかの向きに垂直に包丁で1回切る感じになる
  // a, b, cのどれかが偶数ならその方向に切れば差は0
  if (a % 2 == 0 || b % 2 == 0 || c % 2 == 0) {
    cout << 0 << endl;
    return 0;
  }
  // 奇数なら、各方向に差1で切るので、切り口の面積が差になる
  cout << llMin(a * b, llMin(a * c, b * c)) << endl;

  return 0;
}