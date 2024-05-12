#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  string s;
  cin >> s;

  int ans = 10000;
  int num;
  rep(i, s.length() - 2) {
    num = stoi(s.substr(i, 3));
    // cout << num << endl;
    ans = min(ans, abs(753 - num));
  }

  cout << ans << endl;

  return 0;
}