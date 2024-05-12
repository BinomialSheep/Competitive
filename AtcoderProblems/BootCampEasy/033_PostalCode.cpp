#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int A, B;
  string S;
  cin >> A >> B >> S;

  bool isYes = true;
  rep(i, S.length()) {
    if (i == A) {
      if (S[i] != '-') {
        isYes = false;
      }
    } else if (S[i] == '-') {
      isYes = false;
      break;
    }
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}