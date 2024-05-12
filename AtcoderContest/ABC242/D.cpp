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
    if (t == 0) {
      cout << S[k] << endl;
      continue;
    }
    //
    ll expo;
    if (t >= 63)
      expo = pow(2, 62);
    else
      expo = pow(2, t);

    // St[k]がS0の何番目の文字から生成されるか求める
    ll start = k / expo;
    if (k % expo != 0) start++;
    // cout << start;

    char nowChar = S[start];
    k -= (start - 1) * expo;
    for (int j = t - 1; j >= 0; j--) {
      ll center = expo / 2;
      if (k <= center) {
        // 前半なら前半の遷移
        if (nowChar == 'A')
          nowChar = 'B';
        else if (nowChar == 'B')
          nowChar = 'C';
        else
          nowChar = 'A';
      } else {
        k -= center;
        if (nowChar == 'A')
          nowChar = 'C';
        else if (nowChar == 'B')
          nowChar = 'A';
        else
          nowChar = 'B';
      }
    }

    cout << nowChar << endl;
  }

  return 0;
}