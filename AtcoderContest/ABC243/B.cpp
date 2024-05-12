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
  int n;
  cin >> n;
  vector<int> A(n);
  vector<int> B(n);
  rep(i, n) cin >> A[i];
  rep(i, n) cin >> B[i];
  int ans1 = 0;
  int ans2 = 0;
  rep(i, n) {
    rep(j, n) {
      if (A[i] == B[j]) {
        if (i == j) {
          ans1++;
        } else {
          ans2++;
        }
      }
    }
  }
  cout << ans1 << endl;
  cout << ans2 << endl;

  return 0;
}