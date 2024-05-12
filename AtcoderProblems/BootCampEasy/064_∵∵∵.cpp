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
  string O, E;
  cin >> O >> E;

  string ans = "";
  rep(i, E.length()) {
    ans.push_back(O[i]);
    ans.push_back(E[i]);
  }
  if (O.length() > E.length()) ans.push_back(O[O.length() - 1]);

  cout << ans << endl;

  return 0;
}