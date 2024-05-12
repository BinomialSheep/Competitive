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

  vector<bool> used(26, false);

  rep(i, s.length()) { used[s[i] - 'a'] = true; }

  int index = -1;
  rep(i, 26) {
    if (!used[i]) {
      index = i;
      break;
    }
  }

  if (index == -1) {
    cout << "None" << endl;
  } else {
    char c = 'a' + index;
    cout << c << endl;
  }

  return 0;
}