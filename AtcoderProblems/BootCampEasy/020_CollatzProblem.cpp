#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int s;
  cin >> s;
  vector<bool> A(1001000, false);

  // i = 1
  A[s] = true;
  int value = s;
  // i >= 2
  for (int i = 2;; i++) {
    if (value % 2 == 0)
      value /= 2;
    else
      value = 3 * value + 1;
    // cout << value << " ";
    if (A[value]) {
      cout << i << endl;
      break;
    } else {
      A[value] = true;
    }
  }

  return 0;
}