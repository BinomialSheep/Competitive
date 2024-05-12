#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  int A, B, m;
  cin >> A >> B >> m;
  vector<int> a(A);
  vector<int> b(B);
  rep(i, A) cin >> a[i];
  rep(i, B) cin >> b[i];
  int ans = 1001000;
  int x, y, c;
  // 割引を使うケース
  rep(i, m) {
    cin >> x >> y >> c;
    ans = min(ans, a[x - 1] + b[y - 1] - c);
    // cout << ans << endl;
  }
  // 1番安いもの同士を買うケース
  int aMin = 1001000;
  int bMin = 1001000;
  rep(i, A) aMin = min(aMin, a[i]);
  rep(i, B) bMin = min(bMin, b[i]);

  ans = min(ans, aMin + bMin);

  cout << ans << endl;

  return 0;
}