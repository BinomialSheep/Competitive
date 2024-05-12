#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int n;
  cin >> n;
  if (n >= 64)
    cout << 64 << endl;
  else if (n >= 32)
    cout << 32 << endl;
  else if (n >= 16)
    cout << 16 << endl;
  else if (n >= 8)
    cout << 8 << endl;
  else if (n >= 4)
    cout << 4 << endl;
  else if (n >= 2)
    cout << 2 << endl;
  else
    cout << 1 << endl;
  return 0;
}