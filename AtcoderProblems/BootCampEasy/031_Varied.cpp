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

  vector<bool> used(30, false);
  bool isYes = true;
  rep(i, s.length()) {
    int temp = s[i] - 'a';
    if (used[temp]) {
      isYes = false;
      break;
    } else {
      used[temp] = true;
    }
  }

  cout << (isYes ? "yes" : "no") << endl;

  return 0;
}