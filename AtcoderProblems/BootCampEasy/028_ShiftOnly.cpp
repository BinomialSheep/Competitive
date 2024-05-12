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

  int ans = 1000;
  int ai, count;
  rep(i, n) {
    cin >> ai;
    count = 0;
    while (ai % 2 == 0) {
      count++;
      ai /= 2;
    }
    ans = min(count, ans);
  }

  cout << ans << endl;

  return 0;
}