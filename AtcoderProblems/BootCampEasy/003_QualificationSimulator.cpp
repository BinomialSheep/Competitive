#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int N, A, B;
  cin >> N >> A >> B;
  string S;
  cin >> S;
  int aCount = 0, bCount = 0;
  int length = S.length();
  rep(i, length) {
    if (S[i] == 'a') {
      if (aCount + bCount < A + B) {
        aCount++;
        cout << "Yes" << endl;
      } else {
        cout << "No" << endl;
      }
    } else if (S[i] == 'b') {
      if (aCount + bCount < A + B && bCount < B) {
        bCount++;
        cout << "Yes" << endl;
      } else {
        // 通ってない時はbCountを増やさない
        cout << "No" << endl;
      }
    } else {
      // case c
      cout << "No" << endl;
    }
  }

  return 0;
}