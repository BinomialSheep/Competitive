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

  stack<char> color;
  int ans = 0;

  rep(i, s.size()) {
    if (color.empty()) {
      color.push(s[i]);
      continue;
    }
    char last = color.top();
    if (s[i] != last) {
      color.pop();
      ans += 2;
    } else {
      color.push(s[i]);
    }
  }

  cout << ans << endl;

  return 0;
}