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
  string n;
  cin >> n;
  int ans;
  if (n.length() == 1) {
    // 1桁はそれ
    ans = n[0] - '0';
  } else {
    // 1桁少なくて全部9
    int temp1 = n[0] - '1' + (n.size() - 1) * 9;
    int temp2 = 0;
    rep(i, n.length()) { temp2 += n[i] - '0'; }
    ans = max(temp1, temp2);
  }

  cout << ans << endl;

  return 0;
}