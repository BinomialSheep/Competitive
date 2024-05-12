#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int sumDigits(int num) {
  int n5 = num / 10000;
  int n4 = num / 1000 - 10 * (num / 10000);
  int n3 = num / 100 - 10 * (num / 1000);
  int n2 = num / 10 - 10 * (num / 100);
  int n1 = num - 10 * (num / 10);
  // cout << n5 << n4 << n3 << n2 << n1 << endl;
  return n5 + n4 + n3 + n2 + n1;
}

int main() {
  int n, a, b;
  cin >> n >> a >> b;
  ll ans = 0;
  rep(i, n) {
    int temp = sumDigits(i + 1);
    //cout << temp << endl;
    if (a <= temp && temp <= b) ans += i + 1;
  }

  cout << ans << endl;

  return 0;
}