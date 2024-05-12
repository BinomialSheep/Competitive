#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  string w;
  cin >> w;
  vector<int> counts(27, 0);
  rep(i, w.length()) { counts[w[i] - 'a']++; }

  bool isYes = true;
  for (auto num : counts) {
    if (num % 2 == 1) isYes = false;
  }

  cout << (isYes ? "Yes" : "No") << endl;

  return 0;
}