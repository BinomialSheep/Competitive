#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int n;

ll calc(int i, ll last, ll before) {
  if (i == n)
    return last + before;
  else
    return calc(i + 1, last + before, last);
}

int main() {
  cin >> n;

  if (n == 1) {
    cout << 1 << endl;
  } else {
    cout << calc(2, 1, 2) << endl;
  }

  return 0;
}