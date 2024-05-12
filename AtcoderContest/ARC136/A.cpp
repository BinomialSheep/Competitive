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
  int n;
  string s;
  cin >> n >> s;

  while (true) {
    if (s.rfind("BB") == string::npos && s.rfind("BA") == string::npos) break;

    while (true) {
      if (s.rfind("BB") == string::npos) break;
      s.replace(s.rfind("BB"), 2, "A");
    }
    while (true) {
      if (s.rfind("BA") == string::npos) break;
      s.replace(s.rfind("BA"), 2, "AB");
    }
  }

  cout << s << endl;

  return 0;
}