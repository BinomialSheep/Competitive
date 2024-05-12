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

  int startIndex;
  int endIndex;
  rep(i, s.length()) {
    if (s[i] == 'A') {
      startIndex = i;
      break;
    }
  }
  rep(i, s.length()) {
    if (s[i] == 'Z') endIndex = i;
  }

  cout << endIndex - startIndex + 1 << endl;

  return 0;
}