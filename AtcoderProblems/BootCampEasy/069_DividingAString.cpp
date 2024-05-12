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
  string s;
  cin >> s;
  int n = s.length();

  int count = 0;

  int lastLength = 0;
  rep(i, n) {
    if (i == n - 3) {
      // 残り3個以下は特殊ケース
      if (lastLength == 1) {
        // 後ろから4つ目が1のケース
        if (s[n - 4] != s[n - 3] && s[n - 3] != s[n - 2] &&
            s[n - 2] != s[n - 1]) {
          // 残り3個を1区切りできる時だけ+3
          count += 3;
        } else {
          count += 2;
        }
      } else {
        if (s[n - 3] != s[n - 2] && s[n - 2] != s[n - 1]) {
          // 残り3個を1区切りできる時だけ+3
          count += 3;
        } else {
          count += 2;
        }
      }
      break;
    }

    if (i == n - 2) {
      // 後ろから4個目と3個目が繋がっているケース
      if (s[n - 2] != s[n - 1]) {
        count += 2;
      } else {
        // s[n-2]s[n-1]を1個とする
        // S[n-4][n-3]とs[n-2]s[n-1]が同じでも適当に3:1分割すればいい
        count += 1;
      }
      break;
    }

    if (lastLength != 1) {
      // 1文字で区切る
      count++;
      lastLength = 1;
    } else {
      if (s[i - 1] != s[i]) {
        // 直前と異なる文字なら1文字で区切れる
        count++;
        lastLength = 1;
      } else {
        // 1文字で区切れないので2文字で区切る
        count++;
        i++;
        lastLength = 2;
      }
    }
  }

  cout << count << endl;

  return 0;
}