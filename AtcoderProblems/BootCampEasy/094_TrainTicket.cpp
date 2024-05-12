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
  string s;
  cin >> s;
  int a = s[0] - '0';
  int b = s[1] - '0';
  int c = s[2] - '0';
  int d = s[3] - '0';

  if (a + b + c + d == 7)
    printf("%d+%d+%d+%d=7\n", a, b, c, d);
  else if (a - b + c + d == 7)
    printf("%d-%d+%d+%d=7\n", a, b, c, d);
  else if (a + b - c + d == 7)
    printf("%d+%d-%d+%d=7\n", a, b, c, d);
  else if (a + b + c - d == 7)
    printf("%d+%d+%d-%d=7\n", a, b, c, d);
  else if (a - b - c + d == 7)
    printf("%d-%d-%d+%d=7\n", a, b, c, d);
  else if (a - b + c - d == 7)
    printf("%d-%d+%d-%d=7\n", a, b, c, d);
  else if (a + b - c - d == 7)
    printf("%d+%d-%d-%d=7\n", a, b, c, d);
  else if (a - b - c - d == 7)
    printf("%d-%d-%d-%d=7\n", a, b, c, d);

  return 0;
}