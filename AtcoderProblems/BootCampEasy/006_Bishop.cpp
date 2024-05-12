#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  ll h, w;
  cin >> h >> w;

  if (w == 1) {
    cout << 1 << endl;
  } else {
    // hが1か偶数か3以上の奇数かで場合分け
    if (h == 1) {
      cout << 1 << endl;
    } else if (h % 2 == 0) {
      cout << h / 2 * w << endl;
    } else {
      if (w % 2 == 0) {
        cout << ((h + 1) / 2) * w / 2 + ((h + 1) / 2 - 1) * w / 2 << endl;
      } else {
        cout << ((h + 1) / 2) * ((w + 1) / 2) + ((h - 1) / 2) * (w - 1) / 2
             << endl;
      }
    }
  }

  return 0;
}