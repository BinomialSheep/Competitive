#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int a, b;
  cin >> a >> b;

  int ans = -1;
  rep(i, 2000) {
    if ((int)(i * 0.08) == a && (int)(i * 0.1) == b) {
      ans = i;
      break;
    }
  }

  cout << ans << endl;

  return 0;
}