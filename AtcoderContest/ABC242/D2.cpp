#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// #include <atcoder/all>
// g++ --std=c++14 -I "/mnt/c/Program Files (x86)/Microsoft Visual
// Studio/2019/Community/VC/Tools/MSVC/14.29.30037/include" code.cpp
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define MAX 10000
#define INFTY (1 << 29)
// 浮動小数点の誤差を考慮した等式
#define EPS (1e-10)
#define equal(a, b) (fabs((a) - (b)) < EPS)

int main() {
  string temp;
  int Q;
  cin >> temp >> Q;
  // indexずらし
  string S = "O" + temp;
  // cout << S << endl;

  ll t;
  ll k;

  rep(i, Q) {
    cin >> t >> k;

    // S0からの文字の変化。+1ならA→B, -1ならA→C
    int change = 0;

    while (true) {
      // cout << "t, k:" << t << ", " << k << endl;
      if (t == 0) break;
      if (k == 1) {
        // kが1になったら直ちに求められる
        if (t % 3 == 1) {
          change++;
          if (change == 2) change = -1;
        } else if (t % 3 == 2)
          change--;
        if (change == -2) change = 1;

        break;
      }
      // 再帰的に求める
      if (k % 2 == 0) {
        // 直前の文字から-1側に遷移する
        change--;
        if (change == -2) change = 1;
        // 直前の文字のindex
        k /= 2;
      } else {
        // 直前の文字から+1側に遷移する
        change++;
        if (change == 2) change = -1;
        // 直前の文字のindex
        k = k / 2 + 1;
      }
      t--;
    }

    char ans = S[k];
    // cout << "ans, change:" << ans << ", " << change << endl;
    if (S[k] == 'A' && change == -1)
      ans = 'C';
    else if (S[k] == 'C' && change == 1)
      ans = 'A';
    else
      ans = S[k] + change;

    cout << ans << endl;
  }

  return 0;
}