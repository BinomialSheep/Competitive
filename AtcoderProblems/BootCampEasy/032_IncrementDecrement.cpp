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
  string s;
  cin >> s;
  int x = 0, ans = 0;

  rep(i, n) {
    if (s[i] == 'I') {
      ans = max(++x, ans);
    } else {
      x--;
    }
  }

  cout << ans << endl;

  return 0;
}