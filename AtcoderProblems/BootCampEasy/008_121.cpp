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
  int c = stoi(a + b);

  int flag = 0;
  rep(i, 400) {
    if (i * i == c) {
      flag = 1;
      break;
    }
  }
  if (flag == 1)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;

  return 0;
}