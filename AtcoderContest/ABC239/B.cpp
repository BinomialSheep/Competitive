#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll x;
  cin >> x;
  if (x >= 0) {
    cout << x / 10 << endl;
  } else {
    if (x % 10 == 0) {
      cout << x / 10 << endl;
    } else {
      cout << x / 10 - 1 << endl;
    }
  }

  return 0;
}