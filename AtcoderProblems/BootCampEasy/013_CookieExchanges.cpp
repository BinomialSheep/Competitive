#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int a, b, c;
  cin >> a >> b >> c;

  int ans = 0;
  int temp1, temp2;
  while (true) {
    if (a % 2 == 1 || b % 2 == 1 || c % 2 == 1) break;

    if (a == b && b == c) {
      ans = -1;
      break;
    }
    temp1 = a;
    temp2 = b;
    a = (b + c) / 2;
    b = (temp1 + c) / 2;
    c = (temp1 + temp2) / 2;
    ans++;
  }

  cout << ans << endl;

  return 0;
}