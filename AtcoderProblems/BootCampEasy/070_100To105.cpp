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
  int x;
  cin >> x;
  int ans = 0;

  if (x >= 2200) {
    ans = 1;
  } else {
    rep(i1, 23) {
      rep(i2, 23) {
        rep(i3, 23) {
          rep(i4, 23) {
            rep(i5, 23) {
              rep(i6, 23) {
                if (i1 * 100 + i2 * 101 + i3 * 102 + i4 * 103 + i5 * 104 +
                        i6 * 105 ==
                    x) {
                  ans = 1;
                  break;
                }
              }
            }
          }
        }
      }
    }
  }

  cout << ans << endl;

  return 0;
}