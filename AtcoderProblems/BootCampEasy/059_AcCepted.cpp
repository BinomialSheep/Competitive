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
  bool isAC = true;
  int countC = 0;
  rep(i, s.length()) {
    if (i == 0) {
      if (s[i] == 'A')
        continue;
      else {
        isAC = false;
        break;
      }
    }
    if (2 <= i && i <= s.length() - 2 && countC == 0 && s[i] == 'C') {
      countC = 1;
      continue;
    }
    if ('A' <= s[i] && s[i] <= 'Z') {
      isAC = false;
      break;
    }
  }
  if (countC == 0) isAC = false;

  cout << (isAC ? "AC" : "WA") << endl;

  return 0;
}