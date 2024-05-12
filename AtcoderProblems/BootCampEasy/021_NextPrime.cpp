#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int x;
  cin >> x;
  int ans;

  // 以下は2を処理できないので2を例外的にearly return
  if (x == 2) {
    cout << 2 << endl;
    return 0;
  }

  for (int i = x;; i++) {
    ans = i;
    for (int j = 2; j < i; j++) {
      if (i % j == 0) {
        ans = -1;
        break;
      }
    }
    if (ans != -1) break;
  }
  cout << ans << endl;

  return 0;
}