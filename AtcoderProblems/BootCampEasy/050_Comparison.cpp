#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  string a, b;
  cin >> a >> b;
  if (a.length() > b.length()) {
    cout << "GREATER" << endl;
  } else if (a.length() < b.length()) {
    cout << "LESS" << endl;
  } else {
    rep(i, a.length()) {
      if (a[i] > b[i]) {
        cout << "GREATER" << endl;
        return 0;
      } else if (a[i] < b[i]) {
        cout << "LESS" << endl;
        return 0;
      }
    }
    cout << "EQUAL" << endl;
  }

  return 0;
}