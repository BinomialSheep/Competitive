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

  // 0101...にする場合
  int scoreA = 0;
  rep(i, s.length()) {
    if (i % 2 == 0 && s[i] == '1')
      scoreA++;
    else if (i % 2 == 1 && s[i] == '0')
      scoreA++;
  }
  // 1010...にする場合
  int scoreB = 0;
  rep(i, s.length()) {
    if (i % 2 == 0 && s[i] == '0')
      scoreB++;
    else if (i % 2 == 1 && s[i] == '1')
      scoreB++;
  }

  cout << min(scoreA, scoreB) << endl;

  return 0;
}