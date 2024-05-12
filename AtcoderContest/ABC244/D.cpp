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
  char s1, s2, s3, t1, t2, t3;
  cin >> s1 >> s2 >> s3 >> t1 >> t2 >> t3;

  /* solve */
  // 偶置換ならOK
  if (s1 == t1) {
    if (s2 == t2) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  } else if (s1 == t2) {
    if (s2 == t1) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  } else if (s1 == t3) {
    if (s2 == t2) {
      cout << "No" << endl;
    } else {
      cout << "Yes" << endl;
    }
  }

  return 0;
}