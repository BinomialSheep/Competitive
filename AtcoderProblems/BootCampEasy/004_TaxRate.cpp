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

  int start = n / 1.20;

  for (int i = start; i <= n; i++) {
    double price = i * 1.08;
    if (price < n) continue;
    if (n <= price && price < n + 1) {
      cout << i << endl;
      break;
    }
    cout << ":(" << endl;
    break;
  }

  return 0;
}