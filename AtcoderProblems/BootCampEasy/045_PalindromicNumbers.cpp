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
  string s;
  int ans = 0;
  for (int i = a; i <= b; i++) {
    s = to_string(i);
    if (s[0] == s[4] && s[1] == s[3]) ans++;
  }

  cout << ans << endl;

  return 0;
}