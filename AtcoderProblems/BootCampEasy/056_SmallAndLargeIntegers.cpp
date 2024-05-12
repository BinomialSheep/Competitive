#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int a, b, k;
  cin >> a >> b >> k;
  int ak = a + k - 1;
  int bk = b - k + 1;

  ak = min(ak, b);
  bk = max(a, bk);

  // 範囲がかぶさる場合の調整
  if (ak >= bk) bk = ak + 1;

  for (int i = a; i <= ak; i++) {
    cout << i << endl;
  }
  for (int i = bk; i <= b; i++) {
    cout << i << endl;
  }

  return 0;
}