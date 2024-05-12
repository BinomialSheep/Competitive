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
  bool isYes = true;
  bool existN = s.find('N') != string::npos;
  bool existS = s.find('S') != string::npos;
  bool existE = s.find('E') != string::npos;
  bool existW = s.find('W') != string::npos;

  if (existN && !existS) isYes = false;
  if (existS && !existN) isYes = false;
  if (existE && !existW) isYes = false;
  if (existW && !existE) isYes = false;

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}