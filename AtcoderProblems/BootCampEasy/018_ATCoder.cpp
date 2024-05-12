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

  int maxLength = 0;
  int length = 0;

  rep(i, s.length()) {
    if (s[i] == 'A' || s[i] == 'C' || s[i] == 'G' || s[i] == 'T') {
      length++;

      if (i == s.length() - 1 && length > maxLength) maxLength = length;
    } else {
      if (length > maxLength) maxLength = length;
      length = 0;
    }
  }

  cout << maxLength << endl;

  return 0;
}