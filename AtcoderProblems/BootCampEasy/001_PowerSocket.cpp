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

  int n;
  // n個使った時のタップの数
  rep(i, 30) {
    if ((a - 1) * i + 1 >= b) {
      cout << i << endl;
      break;
    }
  }

  return 0;
}