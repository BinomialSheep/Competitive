#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll a, b;
  cin >> a >> b;

  if (a <= 0 && 0 <= b) {
    cout << "Zero" << endl;
  } else if (b > 0) {
    cout << "Positive" << endl;
  } else {
    // 両方負
    ll minusNum = b - a + 1;
    cout << (minusNum % 2 == 0 ? "Positive" : "Negative") << endl;
  }

  return 0;
}